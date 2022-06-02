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
	lateralBarsAnim.PushBack({ 0,0,2,15 });//pink
	lateralBarsAnim.PushBack({ 2,0,2,15 });//red
	lateralBarsAnim.PushBack({ 4,0,2,15 });//orange
	lateralBarsAnim.PushBack({ 6,0,2,15 });//yellow
	lateralBarsAnim.PushBack({ 8,0,2,15 });//white
	lateralBarsAnim.PushBack({ 10,0,2,15 });//green
	lateralBarsAnim.PushBack({ 12,0,2,15 });//cyan
	lateralBarsAnim.PushBack({ 14,0,2,15 });//blue
	lateralBarsAnim.loop = true;
	lateralBarsAnim.speed = 0.2f;
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
	lateralBars = App->textures->Load("Assets/Sprites/lateralBars.png");

	lateralBarCounter = 0;

	lateralBarsY = 0;
	App->audio->PlayMusic("", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	play_diff = false;
	selection = 0;
	timer = 0;
	lateralBarCounter = 0;

	lateralBarsY = 0, lateralBarsX = 0;

	return ret;
}

Update_Status SceneMenu::Update()
{
	lateralBarsAnim.Update();
	lateralBarCounter++;

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
	//counter to change lateral bars position
	if (lateralBarCounter==17)
	{
		lateralBarCounter = 0;
	}
	else if (lateralBarCounter == 1)
	{
		lateralBarsY = 0, lateralBarsX = 0;
	}
	else if (lateralBarCounter == 3)
	{
		lateralBarsY = 35, lateralBarsX = 0;
	}
	else if (lateralBarCounter == 6)
	{
		lateralBarsY = 70, lateralBarsX = 0;
	}
	else if (lateralBarCounter == 9)
	{
		lateralBarsY = 70, lateralBarsX = 88;
	}
	else if (lateralBarCounter == 12)
	{
		lateralBarsY = 35, lateralBarsX = 88;
	}
	else if (lateralBarCounter == 15)
	{
		lateralBarsY = 0, lateralBarsX = 88;
	}

	// Draw everything --------------------------------------
	if (play_diff) // If Difficulty menu is true
	{
		App->render->Blit(diffbgTexture, 0, 0, NULL);
		switch (selection)
		{
		 case 0: //Easy Difficulty Arrows
			 App->render->Blit(rightArrow, 31, 33, NULL);
			 App->render->Blit(leftArrow, 71, 33, NULL);
			 App->render->Blit(lateralBars, 12 + lateralBarsX, 86 + lateralBarsY, &(lateralBarsAnim.GetCurrentFrame()));
			 break;
		 case 1: //Normal Difficulty Arrows
			 App->render->Blit(rightArrow, 136, 33, NULL);
			 App->render->Blit(leftArrow, 192, 33, NULL);
			 App->render->Blit(lateralBars, 123 + lateralBarsX, 86 + lateralBarsY, &(lateralBarsAnim.GetCurrentFrame()));

			 break;
		 case 2: //Hard Difficulty Arrows
			 App->render->Blit(rightArrow, 256, 33, NULL);
			 App->render->Blit(leftArrow, 296, 33, NULL);
			 App->render->Blit(lateralBars, 236 + lateralBarsX, 86 + lateralBarsY, &(lateralBarsAnim.GetCurrentFrame()));
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
			App->render->Blit(lateralBars, 12 + lateralBarsX * 1.64, 86 + lateralBarsY, &(lateralBarsAnim.GetCurrentFrame()));
			break;
		 case 1: //Multiplayer Arrows
			App->render->Blit(rightArrow, 215, 33, NULL);
			App->render->Blit(leftArrow, 289, 33, NULL);
			App->render->Blit(lateralBars, 180 + lateralBarsX * 1.64, 86 + lateralBarsY, &(lateralBarsAnim.GetCurrentFrame()));
			break;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneMenu::CleanUp()
{
	LOG("Deleting background assets");

	App->textures->Unload(modebgTexture);
	App->textures->Unload(diffbgTexture);
	App->textures->Unload(rightArrow);
	App->textures->Unload(leftArrow);
	App->textures->Unload(lateralBars);


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
