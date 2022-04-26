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
	//INPUT
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
	{
		
	}
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
	{

	}
	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
	{

	}
	return Update_Status::UPDATE_CONTINUE;

	//HIT walls and flor
	//if hit == true
	//check for line


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

				++App->player->lines;

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

	}



	return Update_Status::UPDATE_CONTINUE;
}

bool ModulePlayGround::CleanUp()
{
	return true;
}
