#include "ModulePlayGround.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"

#include <stdio.h>

#include "SDL/include/SDL.h"

ModulePlayGround::ModulePlayGround(bool startEnabled) : Module(startEnabled) {}

ModulePlayGround::~ModulePlayGround() {}


bool ModulePlayGround::Start()
{
	srand(time(NULL));
	nextBlock.id = RandomBlock();
	NextBlock();

	return true;
}

Update_Status ModulePlayGround::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayGround::Update()
{
	if (App->player->stateLine == true) 
	{
		fCountL++;

		if (fCountL == 2)
		{
			StateLine();
			fCountL = 0;
		}
		return Update_Status::UPDATE_CONTINUE;
	}

	if (App->player->statePlay == true)
	{
		StatePlay();

		return Update_Status::UPDATE_CONTINUE;
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



// STATES =============================================

void ModulePlayGround::StateLine()
{
	int line = linePositionList[linePositionIndex];

	//check for last line
	if (line == -1 || linePositionIndex == 4)
	{
		linePositionIndex = 0;
		App->player->stateLine = false;
		App->player->statePlay = true;

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
				App->sceneLevel_1->playground[i][j] = App->sceneLevel_1->playground[i - 1][j];
		}

		lineColorIndex = 0;
		linePositionIndex++;
	}
	else
	{
		//set rainbow color
		for (size_t j = 1; j < 11; j++)
			App->sceneLevel_1->playground[line][j] = lineColorList[lineColorIndex];
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
	}

	SaveInput();

	//Y movement
	fCountY++;
	if (fCountY == 40 / block.inputY)
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

		fCountY = 0;
	}
	else if (fCountY > 40 / block.inputY)
		fCountY = 0;

	//X movement
	fCountX++;
	if (fCountX == 20)
	{
		if (block.inputX != 0)
		{
			if (!IsColliding(block.x + block.inputX, block.y, block))
				MoveBlock(block.x + block.inputX, block.y);
		}

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

		fCountX = 0;
		block.inputX = 0;
	}
}


// LOGIC ===========================================================

void ModulePlayGround::SaveInput()
{
	block.inputY = 1;

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT) { block.inputX = -1; }
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT) { block.inputY = 20; }
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT) { block.inputX = 1; }
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN) { rotate = true; }

	// DEBUG KEYS
	if (App->input->keys[SDL_SCANCODE_F1] == Key_State::KEY_DOWN) { App->sceneLevel_1->levelLines = 0; }
	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN) { gameOver = true; }
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) { lineLimit = !lineLimit; }
	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN) { selectBlock = !selectBlock; }

	if (selectBlock == true)
	{
		if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN) { blockSpawnID = 0; }
		if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN) { blockSpawnID = 1; }
		if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN) { blockSpawnID = 2; }
		if (App->input->keys[SDL_SCANCODE_4] == Key_State::KEY_DOWN) { blockSpawnID = 3; }
		if (App->input->keys[SDL_SCANCODE_5] == Key_State::KEY_DOWN) { blockSpawnID = 4; }
		if (App->input->keys[SDL_SCANCODE_6] == Key_State::KEY_DOWN) { blockSpawnID = 5; }
		if (App->input->keys[SDL_SCANCODE_7] == Key_State::KEY_DOWN) { blockSpawnID = 6; }
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
			if (block.tiles[i][j] && App->sceneLevel_1->playground[y2 + i][x2 + j] != 0)
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
				App->sceneLevel_1->playground[block.y + i][block.x + j] = block.tiles[i][j];
				App->audio->PlayFx(App->audio->hitFx);
			}
		}
	}
}

bool ModulePlayGround::GameoverCheck()
{
	for (size_t i = 1; i < 11; i++)
	{
		if (App->sceneLevel_1->playground[1][i] != 0)
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
			if (App->sceneLevel_1->playground[i][j] != 0)
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
		App->player->stateLine = true;
		App->player->statePlay = false;
	}
}

void ModulePlayGround::Score()
{
	//lines
	switch (lines)
	{
	case 1: App->player->score += 50; break;
	case 2: App->player->score += 150; break;
	case 3: App->player->score += 400; break;
	case 4: App->player->score += 900; break;
	default: break;
	}

	//passive
	int gravity = 1;
	int rainbow = App->player->rainbow;
	height = (height - 21) * -1;

	if (block.inputY == 20)
		gravity = 2;

	App->player->score += gravity * rainbow * (rainbow + height);

	App->player->totalLines += lines;
	App->sceneLevel_1->levelLines-=lines;
}