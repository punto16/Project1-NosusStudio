#include "ModulePlayGround.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleGame.h"
#include "SceneGame.h"

#include <stdio.h>

#include "SDL/include/SDL.h"

ModulePlayGround::ModulePlayGround(bool startEnabled) : Module(startEnabled) {}

ModulePlayGround::~ModulePlayGround() {}


bool ModulePlayGround::Start()
{
	srand(time(NULL));
	nextBlock.id = RandomBlock();

	lineLimit = false;
	selectBlock = false;

	return true;
}

Update_Status ModulePlayGround::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayGround::Update()
{
	if (App->game->stateWin)
	{
		if (App->sceneGame->winDelay <= 120 && bonus == false && delayBonus == 0)
		{
			Bonus();
		}
		
		delayBonus--;
		if (delayBonus < 0) { delayBonus = 5; }

		Blink();
	}

	if (App->game->stateLine1 == true)
	{
		fCountL++;

		if (fCountL == 2)
		{
			StateLine();
			fCountL = 0;
		}
	}

	if (App->game->statePlay1 == true)
	{
		StatePlay();
	}

	blink++;
	if (blink > 59) {
		blink = 0;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayGround::PostUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

bool ModulePlayGround::CleanUp()
{
	return true;
}



// STATES ==========================================================

void ModulePlayGround::StateLine()
{
	int line = linePositionList[linePositionIndex];

	//check for last line
	if (line == -1 || linePositionIndex == 4)
	{
		linePositionIndex = 0;
		App->game->stateLine1 = false;
		App->game->statePlay1 = true;

		for (int i = 0; i < 4; i++)
			linePositionList[i] = -1;
	}
	else if (lineColorIndex == 6)
	{
		App->audio->PlayFx(App->audio->lineFx);
		//move lines down
		for (int i = line; i > 0; i--)
		{
			for (int j = 1; j < 11; j++)
				App->sceneGame->playground[i][j] = App->sceneGame->playground[i - 1][j];
		}
		App->sceneGame->levelLines --;
		if (App->sceneGame->levelLines < 0) { App->sceneGame->levelLines = 0; }

		lineColorIndex = 0;
		linePositionIndex++;
	}
	else
	{
		//set rainbow color
		for (size_t j = 1; j < 11; j++)
			App->sceneGame->playground[line][j] = lineColorList[lineColorIndex];
		lineColorIndex++;
	}
}

void ModulePlayGround::StatePlay()
{
	if (isAlive == false)
	{
		DeathSequence();
		gameOver = GameoverCheck();
		CheckLine();
		Score();
		NextBlock();

		fCountPress = 1;
	}

	SaveInput();

	//Y movement
	fCountY++;
	if (fCountY == 20 / block.inputY)
	{
		if (block.inputY != 0)
		{
			if (!IsColliding(block.x, block.y + 1, block))
				MoveBlock(block.x, block.y + 1);
			else
				isAlive = false;
		}
		else if (!IsColliding(block.x, block.y + 1, block)) //block fall
			MoveBlock(block.x, block.y + 1);

		fCountPress += 2;
		fCountY = 0;
	}
	else if (fCountY > 20 / block.inputY)
		fCountY = 1;


	//X movement
	if (fCountX >= 10)
	{
		if (block.inputX != 0)
		{
			if (!IsColliding(block.x + block.inputX, block.y, block))
				MoveBlock(block.x + block.inputX, block.y);
		}
		fCountX = 0;
	}
	block.inputX = 0;


	//Rotate
	if (rotate == true)
	{
		blockCheck.id = block.id;
		blockCheck.rotation = block.rotation + 1;
		if (blockCheck.rotation == 4) { blockCheck.rotation = 0; }

		LoadBlockMatrix(blockCheck);

		if (!IsColliding(block.x, block.y, blockCheck))
		{
			RotateBlock();
		}
		else
		{
			if (!IsColliding(block.x - 1, block.y, blockCheck))
			{
				MoveBlock(block.x - 1, block.y);
				RotateBlock();
			}
		}
		rotate = false;
	}
}


// LOGIC ===========================================================

void ModulePlayGround::SaveInput()
{
	//CONTROLS

	//Y 
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) { block.inputY = fCountPress > 14 ? 14 : fCountPress; }		
	else { fCountPress = 1; block.inputY = 1; }
	
	//X keydown
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) { block.inputX = -1; fCountX = 10; }
	else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN) { block.inputX = 1; fCountX = 10; }
	else
	{
		//X repeat
		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT ||
			App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
		{
			fCountX++;
		}
		if (fCountX == 10)
		{
			if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) { block.inputX = -1; }
			else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) { block.inputX = 1; }
		}
	}
	
	//rotate
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) { rotate = true; }

	// DEBUG KEYS
	if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN) { App->sceneGame->levelLines = 0; }	//win
	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN) { gameOver = true; }					//lose
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) { lineLimit = !lineLimit; }			//unlimited line mode
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) { selectBlock = !selectBlock; }		//lock nextblock to selection(1-7)
	if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN) { App->game->totalLines++; }    //Add lines to player total lines
  
	if (selectBlock == true)
	{
		if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN) { blockSpawnID = 0; }
		else if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN) { blockSpawnID = 1; }
		else if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN) { blockSpawnID = 2; }
		else if (App->input->keys[SDL_SCANCODE_4] == Key_State::KEY_DOWN) { blockSpawnID = 3; }
		else if (App->input->keys[SDL_SCANCODE_5] == Key_State::KEY_DOWN) { blockSpawnID = 4; }
		else if (App->input->keys[SDL_SCANCODE_6] == Key_State::KEY_DOWN) { blockSpawnID = 5; }
		else if (App->input->keys[SDL_SCANCODE_7] == Key_State::KEY_DOWN) { blockSpawnID = 6; }
	}
}

void ModulePlayGround::NextBlock()
{
	block.id = nextBlock.id;
	block.on_playground = true;
	nextBlock.id = RandomBlock();
	block.rotation = 0;
	block.x = 5;
	block.y = 0;
	LoadBlockMatrix(block);
	isAlive = true;
}

int ModulePlayGround::RandomBlock()
{
	if (selectBlock == false) {
		blockSpawnID = rand() % 7;
	}

	return blockSpawnID;
}

void ModulePlayGround::LoadBlockMatrix(Block& block)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
			block.tiles[i][j] = blockList[block.id][block.rotation][i][j];
	}
}

bool ModulePlayGround::IsColliding(int x2, int y2, Block& block)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (block.tiles[i][j] && App->sceneGame->playground[y2 + i][x2 + j] != 0)
			{
				height = block.y + i;
				return true;
			}
		}
	}
	return false;
}

void ModulePlayGround::MoveBlock(int x2, int y2)
{
	block.x = x2;
	block.y = y2;
}

void ModulePlayGround::RotateBlock()
{
	block.rotation++;
	if (block.rotation == 4) { block.rotation = 0; }

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
			block.tiles[i][j] = blockList[block.id][block.rotation][i][j];
	}
}

void ModulePlayGround::DeathSequence()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (block.tiles[i][j] != 0)
			{
				App->sceneGame->playground[block.y + i][block.x + j] = block.tiles[i][j];
				App->audio->PlayFx(App->audio->hitFx);
			}
		}
	}
}

bool ModulePlayGround::GameoverCheck()
{
	for (size_t i = 1; i < 11; i++)
	{
		if (App->sceneGame->playground[1][i] != 0)
		{
			return true;
		}
	}

	return false;
}

void ModulePlayGround::CheckLine()
{
	int count;
	lines = 0;

	for (size_t i = 0; i < 22; i++)
	{
		count = 0;

		for (size_t j = 0; j < 12; j++)
		{
			if (App->sceneGame->playground[i][j] != 0)
			{
				count++;
			}
		}
		if (count == 12)
		{
			linePositionList[lines] = i;
			lines++;
		}
	}

	if (lines > 0)
  {
		App->game->stateLine1 = true;
		App->game->statePlay1 = false;
		CutTextures();
	}
}

void ModulePlayGround::Score()
{
	//lines
	switch (lines)
	{
	case 1: App->game->scorePlayer1 += 50;  break;
	case 2: App->game->scorePlayer1 += 150; break;
	case 3: App->game->scorePlayer1 += 400; break;
	case 4: App->game->scorePlayer1 += 900; break;
	default: break;
	}

	//passive
	int gravity = 1;
	int rainbow = App->game->rainbow;
	height = (height - 21) * -1;

	if (block.inputY == 20)
		gravity = 2;

	App->game->scorePlayer1 += gravity * rainbow * (rainbow + height);

	App->game->totalLines += lines;

}

void ModulePlayGround::CutTextures() {
	int line_up = (linePositionList[0])-1;
	int line_down = (linePositionList[lines-1])+1;

	for (size_t i = 1; i < 11; i++) {
		switch ((App->sceneGame->playground[line_up][i])%15)
		{
		case 4:
			App->sceneGame->playground[line_up][i] += 11;
			break;
		case 5:
			App->sceneGame->playground[line_up][i] += 1;
			break;
		case 8:
			App->sceneGame->playground[line_up][i] += 5;
			break;
		case 9:
			App->sceneGame->playground[line_up][i] -= 7;
			break;
		case 10:
			App->sceneGame->playground[line_up][i] += 2;
			break;
		case 11:
			App->sceneGame->playground[line_up][i] -= 10;
			break;
		case 14:
			App->sceneGame->playground[line_up][i] -= 11;
			break;
		default:
			break;
		}
	}

	if (line_down<22) {
		for (size_t j = 1; j < 11; j++) {
			switch ((App->sceneGame->playground[line_down][j]) % 15)
			{
			case 5:
				App->sceneGame->playground[line_down][j] -= 1;
				break;
			case 6:
				App->sceneGame->playground[line_down][j] += 9;
				break;
			case 7:
				App->sceneGame->playground[line_down][j] -= 5;
				break;
			case 8:
				App->sceneGame->playground[line_down][j] += 3;
				break;
			case 10:
				App->sceneGame->playground[line_down][j] += 4;
				break;
			case 12:
				App->sceneGame->playground[line_down][j] -= 9;
				break;
			case 13:
				App->sceneGame->playground[line_down][j] -= 12;
				break;
			default:
				break;
			}
		}
	}
}

void ModulePlayGround::Bonus() {	
	
	if (lastBonus < 22) {
		for (size_t j = 1; j < 11; j++)
		{
			if (App->sceneGame->playground[lastBonus][j] != 0)
			{
				bonus = true;
			}
		}
		if (bonus == false) {
			for (int j = 1; j < 11; j++) {
				if (j == 1) { App->sceneGame->playground[lastBonus][j] = 106; }
				else if (j == 10) { App->sceneGame->playground[lastBonus][j] = 108; }
				else { App->sceneGame->playground[lastBonus][j] = 107; }
			}
			App->game->scorePlayer1 += bonusPoints;
			bonusPoints += 10;
		}
		lastBonus++;
	}	
}

void ModulePlayGround::Blink() {
	if(blink<30)
	{
		for (size_t i = 2; i < 22; i++)
		{
			for (int j = 1; j < 11; j++) {
				if (j == 1 && App->sceneGame->playground[i][j] == 106) { App->sceneGame->playground[i][j] = 121; }
				else if (j == 10 && App->sceneGame->playground[i][j] == 108) { App->sceneGame->playground[i][j] = 123; }
				else if (App->sceneGame->playground[i][j] == 107) { App->sceneGame->playground[i][j] = 122; }
			}
		}
	}
	else
	{
		for (size_t i = 2; i < 22; i++)
		{
			for (int j = 1; j < 11; j++) {
				if (j == 1 && App->sceneGame->playground[i][j] == 121) { App->sceneGame->playground[i][j] = 106; }
				else if (j == 10 && App->sceneGame->playground[i][j] == 123) { App->sceneGame->playground[i][j] = 108; }
				else if (App->sceneGame->playground[i][j] == 122) { App->sceneGame->playground[i][j] = 107; }
			}
		}
	}
}

void ModulePlayGround::RandomBlockSpawn() {

	int SpawnX = (rand() % 11) + 1;
	for (int i = 0; i < 22; i++) {
		if (App->sceneGame->playground[i + 1][SpawnX] > 0) {
			App->sceneGame->playground[i][SpawnX] = 120;
			break;
		}
	}
}

void ModulePlayGround::GarbageSpawn() {

	for (int i = 0; i < 22; i++) {
		int counter = 0;
		for (int j = 1; j < 11; j++) {
			if (i != 21) {
				App->sceneGame->playground[i][j] = App->sceneGame->playground[i + 1][j];
			}
			else if (i == 21) {
				if (j == 10 && counter == 9) {
					App->sceneGame->playground[i][j] = 0;
				}
				else {
					App->sceneGame->playground[i][j] = ((rand() % 9) * 15) - 15;
					if (App->sceneGame->playground[i][j] != 0) {
						counter++;
					}
				}
			}
		}
	}

}