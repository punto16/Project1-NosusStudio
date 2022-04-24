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
			for (size_t i = 0; i < 10; i++)
			{
				for (size_t j = 0; j < 20; j++)
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
}

Update_Status ModulePlayGround::PostUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

bool ModulePlayGround::CleanUp()
{
	return true;
}
