#include "SceneMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneIntro.h"

SceneMenu::SceneMenu(bool startEnabled) : Module(startEnabled)
{

}

SceneMenu::~SceneMenu()
{

}

// Load assets
bool SceneMenu::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	modebgTexture = App->textures->Load("Assets/Sprites/selectplayer_tetris.png");
	diffbgTexture = App->textures->Load("Assets/Sprites/difficulty_tetris.png");
    rightArrow = App->textures->Load("Assets/Sprites/arrowRight.png");
	leftArrow = App->textures->Load("Assets/Sprites/arrowLeft.png");

	App->audio->PlayMusic("", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	play_diff = false;
	selection = 0;
	timer = 0;

	return ret;
}

Update_Status SceneMenu::Update()
{
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	else if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN)
	{
		selectionToLeft();
	}
	else if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN)
	{
		selectionToRight();
	}


	if (play_diff == true && timer < 60)
	{
		timer++;
	}
	else if (play_diff && App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && timer >= 60)
	{

		switch (selection)
		{
		case 0: //Easy
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90); //Placeholder
			break;
		case 1: //Normal
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90); //Placeholder
			break;
		case 2: //Hard
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90); //Placeholder
			break;
		}

	}
	else if (!play_diff && App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{

		switch (selection)
		{
		case 0: //Singleplayer
			play_diff = true;
			break;
		case 1: //Multiplayer
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
			break;
		}

	}
	

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	if (play_diff) // If Difficulty menu is true
	{
		App->render->Blit(diffbgTexture, 0, 0, NULL);
		switch (selection)
		{
		 case 0: //Easy Difficulty Arrows
			 App->render->Blit(rightArrow, 31, 33, NULL);
			 App->render->Blit(leftArrow, 71, 33, NULL);
			 break;
		 case 1: //Normal Difficulty Arrows
			 App->render->Blit(rightArrow, 136, 33, NULL);
			 App->render->Blit(leftArrow, 192, 33, NULL);
			 break;
		 case 2: //Hard Difficulty Arrows
			 App->render->Blit(rightArrow, 256, 33, NULL);
			 App->render->Blit(leftArrow, 296, 33, NULL);
			 break;
		}
	}
	else 
	{
		App->render->Blit(modebgTexture, 0, 0, NULL);

		switch (selection)
		{
		 case 0: //Singleplayer Arrows
			App->render->Blit(rightArrow, 47, 33, NULL);
			App->render->Blit(leftArrow, 111, 33, NULL);
			break;
		 case 1: //Multiplayer Arrows
			App->render->Blit(rightArrow, 215, 33, NULL);
			App->render->Blit(leftArrow, 289, 33, NULL);
			break;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneMenu::CleanUp()
{
	LOG("Deleting background assets");

	

	return true;
}

void SceneMenu::selectionToRight()
{
	selection++;

	if (play_diff)
	{
		if (selection > 2) selection = 0;
	}
	else
	{
		if (selection > 1) selection = 0;
	}
}

void SceneMenu::selectionToLeft()
{
	selection--;

	if (play_diff)
	{
		if (selection < 0) selection = 2;
	}
	else
	{
		if (selection < 0) selection = 1;
	}
}
