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

ModulePlayGround::ModulePlayGround(bool startEnabled) : Module(startEnabled)
{
	
}

ModulePlayGround::~ModulePlayGround()
{

}


bool ModulePlayGround::Start()
{
	srand(time(NULL));

	for (int o = 5; o < 5 + NUM_LEVELS; ++o)
	{
		if (App->modules[o]->IsEnabled())
		{
			currentModule = o;
			for (size_t i = 0; i < 10; i++)
			{
				for (size_t j = 0; j < 22; j++)
				{
					map[i][j] = App->modules[o]->PlayGroundGetter(i,j);
				}
			}
		}
	}
	return true;
}

Update_Status ModulePlayGround::PreUpdate()
{


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayGround::Update()
{
	block.id = RandomBlock();
	LoadBlockMatrix();
	
	//block fall
	if (!IsColliding(block.x, block.y + 1))
	{
		MoveBlock(block.x, block.y + 1);
	}

	//input -> check collision -> move/rotate
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
	{
		if (!IsColliding(block.x - 1, block.y))
			MoveBlock(block.x - 1, block.y);
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
	{
		if (!IsColliding(block.x, block.y + 1))
			MoveBlock(block.x, block.y + 1);
	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
	{
		if (!IsColliding(block.x + 1, block.y))
			MoveBlock(block.x + 1, block.y);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		RotateBlock();
	}

	//HIT walls and flor
	//if hit == true
	

	//check for line


	return Update_Status::UPDATE_CONTINUE;
}

	

Update_Status ModulePlayGround::PostUpdate()
{
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

	return Update_Status::UPDATE_CONTINUE;
}

bool ModulePlayGround::CleanUp()
{
	return true;
}


int ModulePlayGround::RandomBlock()
{
	return rand() % 7;
}

void ModulePlayGround::LoadBlockMatrix()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			block.tiles[i][j] = 0;
			block.tiles[i][j] = blockList[block.id][0][i][j];
		}
	}
}

bool ModulePlayGround::IsColliding(int x2, int y2)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (block.tiles[i][j] && map[y2 + i][x2 + j] != 0)
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

}