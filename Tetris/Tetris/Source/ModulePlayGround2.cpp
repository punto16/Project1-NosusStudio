#include "ModulePlayGround2.h"

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

ModulePlayGround2::ModulePlayGround2(bool startEnabled) : Module(startEnabled) {}

ModulePlayGround2::~ModulePlayGround2() {}


bool ModulePlayGround2::Start()
{
	srand(time(NULL));
	nextBlock.id = RandomBlock();

	lineLimit = false;
	selectBlock = false;

	return true;
}

Update_Status ModulePlayGround2::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayGround2::Update()
{
	if (App->game->stateLine2 == true)
	{
		fCountL++;

		if (fCountL == 2)
		{
			StateLine();
			fCountL = 0;
		}
	}

	if (App->game->statePlay2 == true)
	{
		StatePlay();
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayGround2::PostUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

bool ModulePlayGround2::CleanUp()
{
	return true;
}



// STATES ==========================================================

void ModulePlayGround2::StateLine()
{
	int line = linePositionList[linePositionIndex];

	//check for last line
	if (line == -1 || linePositionIndex == 4)
	{
		linePositionIndex = 0;
		App->game->stateLine2 = false;
		App->game->statePlay2 = true;

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
				App->sceneGame->playground2[i][j] = App->sceneGame->playground2[i - 1][j];
		}

		lineColorIndex = 0;
		linePositionIndex++;
	}
	else
	{
		//set rainbow color
		for (size_t j = 1; j < 11; j++)
			App->sceneGame->playground2[line][j] = lineColorList[lineColorIndex];
		lineColorIndex++;
	}
}

void ModulePlayGround2::StatePlay()
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

void ModulePlayGround2::SaveInput()
{
	//CONTROLS

	//Y 
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT) { block.inputY = fCountPress > 14 ? 14 : fCountPress; }
	else { fCountPress = 1; block.inputY = 1; }

	//X keydown
	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN) { block.inputX = -1; fCountX = 10; }
	else if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN) { block.inputX = 1; fCountX = 10; }
	else
	{
		//X repeat
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT ||
			App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			fCountX++;
		}
		if (fCountX == 10)
		{
			if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT) { block.inputX = -1; }
			else if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT) { block.inputX = 1; }
		}
	}

	//rotate
	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_DOWN) { rotate = true; }


	// DEBUG KEYS
	if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN) { App->sceneGame->levelLines = 0; }	//win
	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN) { gameOver = true; }					//lose
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) { lineLimit = !lineLimit; }			//unlimited line mode
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) { selectBlock = !selectBlock; }		//lock nextblock to selection(1-7)
	if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN) { App->game->totalLinesPlayer2++; }   //Adds to player total lines

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

void ModulePlayGround2::NextBlock()
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

int ModulePlayGround2::RandomBlock()
{
	if (selectBlock == false) {
		blockSpawnID = rand() % 7;
	}

	return blockSpawnID;
}

void ModulePlayGround2::LoadBlockMatrix(Block2& block)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
			block.tiles[i][j] = blockList[block.id][block.rotation][i][j];
	}
}

bool ModulePlayGround2::IsColliding(int x2, int y2, Block2& block)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (block.tiles[i][j] && App->sceneGame->playground2[y2 + i][x2 + j] != 0)
			{
				height = block.y + i;
				return true;
			}
		}
	}
	return false;
}

void ModulePlayGround2::MoveBlock(int x2, int y2)
{
	block.x = x2;
	block.y = y2;
}

void ModulePlayGround2::RotateBlock()
{
	block.rotation++;
	if (block.rotation == 4) { block.rotation = 0; }

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
			block.tiles[i][j] = blockList[block.id][block.rotation][i][j];
	}
}

void ModulePlayGround2::DeathSequence()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (block.tiles[i][j] != 0)
			{
				App->sceneGame->playground2[block.y + i][block.x + j] = block.tiles[i][j];
				App->audio->PlayFx(App->audio->hitFx);
			}
		}
	}
}

bool ModulePlayGround2::GameoverCheck()
{
	for (size_t i = 1; i < 11; i++)
	{
		if (App->sceneGame->playground2[1][i] != 0)
		{
			return true;
		}
	}

	return false;
}

void ModulePlayGround2::CheckLine()
{
	int count;
	lines = 0;

	for (size_t i = 0; i < 22; i++)
	{
		count = 0;

		for (size_t j = 0; j < 12; j++)
		{
			if (App->sceneGame->playground2[i][j] != 0)
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

	if (lines > 0) {
		App->game->stateLine2 = true;
		App->game->statePlay2 = false;
		CutTextures();
	}
}

void ModulePlayGround2::Score()
{
	//lines
	switch (lines)
	{
	case 1: App->game->scorePlayer2 += 50; break;
	case 2: App->game->scorePlayer2 += 150; break;
	case 3: App->game->scorePlayer2 += 400; break;
	case 4: App->game->scorePlayer2 += 900; break;
	default: break;
	}

	//passive
	int gravity = 1;
	int rainbow = App->game->rainbow;
	height = (height - 21) * -1;

	if (block.inputY == 20)
		gravity = 2;

	App->game->scorePlayer2 += gravity * rainbow * (rainbow + height);

	App->game->totalLinesPlayer2 += lines;
	//App->sceneGame->levelLines -= lines;
}

void ModulePlayGround2::CutTextures()
{
	int line_up = (linePositionList[0]) - 1;
	int line_down = (linePositionList[lines - 1]) + 1;

	for (size_t i = 1; i < 11; i++)
	{
		switch ((App->sceneGame->playground2[line_up][i]) % 15)
		{								   
		case 4:	 App->sceneGame->playground2[line_up][i] += 11;	break;
		case 5:	 App->sceneGame->playground2[line_up][i] += 1;	break;
		case 8:	 App->sceneGame->playground2[line_up][i] += 5;	break;
		case 9:	 App->sceneGame->playground2[line_up][i] -= 7;	break;
		case 10: App->sceneGame->playground2[line_up][i] += 2;	break;
		case 11: App->sceneGame->playground2[line_up][i] -= 10;	break;
		case 14: App->sceneGame->playground2[line_up][i] -= 11;	break;
		default: break;
		}
	}

	if (line_down < 22)
	{
		for (size_t j = 1; j < 11; j++)
		{
			switch ((App->sceneGame->playground2[line_down][j]) % 15)
			{								   
			case 5:	 App->sceneGame->playground2[line_down][j] -= 1;  break;
			case 6:	 App->sceneGame->playground2[line_down][j] += 9;  break;
			case 7:	 App->sceneGame->playground2[line_down][j] -= 5;  break;
			case 8:	 App->sceneGame->playground2[line_down][j] += 3;  break;
			case 10: App->sceneGame->playground2[line_down][j] += 4;  break;
			case 12: App->sceneGame->playground2[line_down][j] -= 9;  break;
			case 13: App->sceneGame->playground2[line_down][j] -= 12; break;
			default: break;
			}
		}
	}
}