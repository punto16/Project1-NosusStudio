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

ModulePlayGround::ModulePlayGround(bool startEnabled) : Module(startEnabled)
{

}

ModulePlayGround::~ModulePlayGround()
{

}


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
	SaveInput();

	if (isAlive == false)
		NextBlock();

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
		block.inputY = 1;
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

			LoadBlockMatrix(blockCheck);

			if (!IsColliding(block.x, block.y, blockCheck))
			{
				RotateBlock();
			}
			else
			{
				if (!IsColliding(block.x-1, block.y, blockCheck))
				{
					MoveBlock(block.x-1, block.y);
					RotateBlock();
				}
			}

			rotate = false;
		}

		fCountX = 0;
		block.inputX = 0;
	}


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayGround::PostUpdate()
{


	/*
	//line condition

	for (size_t j = 0; j < 22; j++)
	{
		for (size_t i = 0; i < 10 && map[i][j] != ' '; i++)
		{
			if (i == 9)
			{
				//We add a line to the counter, delete the line, and see id the round finished

				//++App->player->lines;

				for (size_t k = 0; k < 10; k++)
				{
					map[k][j] = ' ';
				}
			}
		}
	}

	//victory condition
	if (App->player->lines == App->modules[currentModule]->linesofLevelGetter())
	{
		//App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 90);
	}
	*/





	return Update_Status::UPDATE_CONTINUE;

}

bool ModulePlayGround::CleanUp()
{
	return true;
}


// LOGIC ===========================================================
void ModulePlayGround::SaveInput()
{
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		block.inputX = -1;
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		block.inputY = 20;
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		block.inputX = 1;
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		rotate = true;
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
	return rand() % 7;
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