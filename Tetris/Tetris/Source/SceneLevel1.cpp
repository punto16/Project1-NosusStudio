#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayGround.h"
#include "ModulePlayGround2.h"
#include "ModuleFonts.h"
#include "ModuleTiles.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{
	//animations curtain opening
	curtainOpening.PushBack({ 400,0,80,64 });
	curtainOpening.PushBack({ 320,0,80,64 });
	curtainOpening.PushBack({ 240,0,80,64 });
	curtainOpening.PushBack({ 160,0,80,64 });
	curtainOpening.PushBack({ 80,0,80,64 });
	curtainOpening.PushBack({ 0,0,80,64 });
	curtainOpening.speed = 0.15f;
	curtainOpening.loop = false;

	//animation curtain closing
	curtainClosing.PushBack({ 0,0,80,64 });
	curtainClosing.PushBack({ 80,0,80,64 });
	curtainClosing.PushBack({ 160,0,80,64 });
	curtainClosing.PushBack({ 240,0,80,64 });
	curtainClosing.PushBack({ 320,0,80,64 });
	curtainClosing.PushBack({ 400,0,80,64 });
	curtainClosing.speed = 0.15f;
	curtainClosing.loop = false;

	//lateral bars animation
	lateralBarsAnim.PushBack({ 0,0,2,15 });//pink
	lateralBarsAnim.PushBack({ 2,0,2,15 });//red
	lateralBarsAnim.PushBack({ 4,0,2,15 });//orange
	lateralBarsAnim.PushBack({ 6,0,2,15 });//yellow
	lateralBarsAnim.PushBack({ 8,0,2,15 });//white
	lateralBarsAnim.PushBack({ 10,0,2,15 });//green
	lateralBarsAnim.PushBack({ 12,0,2,15 });//cyan
	lateralBarsAnim.PushBack({ 14,0,2,15 });//blue
	lateralBarsAnim.loop = true;
	lateralBarsAnim.speed = 0.1f;

	//Victory animation 1
	Dance1.PushBack({ 0, 0, 33, 40 });
	Dance1.PushBack({ 33, 0, 33, 40 });
	Dance1.PushBack({ 66, 0, 33, 40 });
	Dance1.PushBack({ 99, 0, 33, 40 });
	Dance1.PushBack({ 132, 0, 33, 40 });
	Dance1.PushBack({ 165, 0, 33, 40 }); //Final puerta
	Dance1.PushBack({ 198, 0, 33, 40 });
	Dance1.PushBack({ 231, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 297, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 330, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 363, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 330, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 297, 0, 33, 40 });
	Dance1.PushBack({ 396, 0, 33, 40 });
	Dance1.PushBack({ 297, 0, 33, 40 });
	Dance1.PushBack({ 429, 0, 33, 40 });
	Dance1.PushBack({ 297, 0, 33, 40 });
	Dance1.PushBack({ 396, 0, 33, 40 });
	Dance1.PushBack({ 297, 0, 33, 40 });
	Dance1.PushBack({ 462, 0, 33, 40 });
	Dance1.PushBack({ 495, 0, 33, 40 });
	Dance1.PushBack({ 528, 0, 33, 40 });
	Dance1.PushBack({ 495, 0, 33, 40 });
	Dance1.PushBack({ 462, 0, 33, 40 });
	Dance1.PushBack({ 495, 0, 33, 40 }); //ESTE FRAME ESTA MAL
	Dance1.PushBack({ 561, 0, 33, 40 });
	Dance1.PushBack({ 495, 0, 33, 40 }); //ESTE FRAME ESTA MAL
	Dance1.PushBack({ 462, 0, 33, 40 });
	Dance1.PushBack({ 495, 0, 33, 40 });
	Dance1.PushBack({ 528, 0, 33, 40 });
	Dance1.PushBack({ 495, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 330, 0, 33, 40 });
	Dance1.PushBack({ 594, 0, 33, 40 });
	Dance1.PushBack({ 330, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 363, 0, 33, 40 });
	Dance1.PushBack({ 627, 0, 33, 40 });
	Dance1.PushBack({ 363, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 330, 0, 33, 40 });
	Dance1.PushBack({ 594, 0, 33, 40 });
	Dance1.PushBack({ 330, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 363, 0, 33, 40 });
	Dance1.PushBack({ 627, 0, 33, 40 });
	Dance1.PushBack({ 363, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 561, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 660, 0, 33, 40 });
	Dance1.PushBack({ 264, 0, 33, 40 });
	Dance1.PushBack({ 231, 0, 33, 40 });
	Dance1.PushBack({ 198, 0, 33, 40 });
	Dance1.PushBack({ 165, 0, 33, 40 });
	Dance1.PushBack({ 132, 0, 33, 40 });
	Dance1.PushBack({ 99, 0, 33, 40 });
	Dance1.PushBack({ 66, 0, 33, 40 });
	Dance1.PushBack({ 33, 0, 33, 40 });
	Dance1.PushBack({ 0, 0, 33, 40 });


	Dance1.loop = false;
	Dance1.speed = 0.1f;

	//Victory animation 2

	//Victory animation 3

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	isCurtainClosing = false;
	curtainClosing.Reset();
	curtainOpening.Reset();

	bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_1.png");
	goTexture = App->textures->Load("Assets/Sprites/gameover.png");
	curtainTexture = App->textures->Load("Assets/Sprites/sprites_courtin.png");
	lateralBars = App->textures->Load("Assets/Sprites/lateralBars.png");
	Russian1 = App->textures->Load("Assets/Sprites/Dance1");
	Russian2 = App->textures->Load("Assets/Sprites/Dance2");
	Russian3 = App->textures->Load("Assets/Sprites/Dance3");


	Dead_Tetromino = App->tiles->Load("Assets/Sprites/tetromino_dead.png", 15, 10);
	
	Alive_Tetromino = App->tiles->Load("Assets/Sprites/tetromino_alive.png", 4, 7);


	App->audio->PlayMusic("Assets/audio/1_Loginska.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->playground->Enable();

	if (App->player->multiplayer == true)
		App->playground2->Enable();

	for (size_t i = 0; i < 23; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			if (playground[i][j] != 255)
				playground[i][j] = 0;
		}
	}

	App->playground->gameOver = false;
	levelLines = 5;

	return ret;
}

Update_Status SceneLevel1::Update()
{
	if (isCurtainClosing == true)
	{
		curtainClosing.Update();
	}

	curtainOpening.Update();
	lateralBarsAnim.Update();
	lateralBarCounter++;
	Dance1.Update();

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	
	//CURTAIN ANIMATION OPENING
	App->render->Blit(curtainTexture, 128, 96, &(curtainOpening.GetCurrentFrame()));
	

	if (isCurtainClosing == true)
	{
		//CURTAIN ANIMATION CLOSING  NOO VA :(
		App->render->Blit(curtainTexture, 128, 96, &(curtainClosing.GetCurrentFrame()));
	}
	
	if (App->playground->lines == 4)
	{
		//counter to change lateral bars position
		if (lateralBarCounter >= 60)
		{
			lateralBarCounter = 0;
		}
		else if (lateralBarCounter == 1)
		{
			lateralBarsY = 24;
		}
		else if (lateralBarCounter == 5)
		{
			lateralBarsY = 46;
		}
		else if (lateralBarCounter == 10)
		{
			lateralBarsY = 69;
		}
		else if (lateralBarCounter == 15)
		{
			lateralBarsY = 91;
		}
		else if (lateralBarCounter == 20)
		{
			lateralBarsY = 115;
		}
		else if (lateralBarCounter == 25)
		{
			lateralBarsY = 0;
		}
		else if (lateralBarCounter == 30)
		{
			lateralBarsY = 24;
		}
		else if (lateralBarCounter == 35)
		{
			lateralBarsY = 46;
		}
		else if (lateralBarCounter == 40)
		{
			lateralBarsY = 69;
		}
		else if (lateralBarCounter == 45)
		{
			lateralBarsY = 91;
		}
		else if (lateralBarCounter == 50)
		{
			lateralBarsY = 115;
		}
		else if (lateralBarCounter == 55)
		{
			App->playground->lines = 0;
		}

		App->render->Blit(lateralBars, 28, 65 + lateralBarsY, &(lateralBarsAnim.GetCurrentFrame()));
		App->render->Blit(lateralBars, 116, 65 + lateralBarsY, &(lateralBarsAnim.GetCurrentFrame()));
	}


  //Draw dead blocks (player 1) 
	for (size_t i = 0; i < 23; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			if (playground[i][j] != 0 && playground[i][j] != 255)
				App->tiles->BlitText(j, i, Dead_Tetromino, playground[i][j], App->playground->block, false);
		}
	}

	if (App->player->multiplayer)	//multiplayer enabled?
	{
		//Draw dead blocks (player 2)
		for (size_t i = 0; i < 23; i++)
		{
			for (size_t j = 0; j < 12; j++)
			{
				if (playground2[i][j] != 0 && playground2[i][j] != 255)
					App->tiles->BlitText2(j, i, Dead_Tetromino, playground2[i][j], App->playground2->block, false);
			}
		}
	}
	

	if (App->playground->gameOver == false)
	{
		//check win condition
		if (levelLines <= 0 && App->playground->lineLimit == false) {
			isCurtainClosing = true;
			App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		}
		else
		{
			//Draw alive block (player 1)
			if (App->playground->nextBlock.id != 255)
				App->tiles->BlitText(8, 24, Alive_Tetromino, NULL, App->playground->nextBlock, true);

			if (App->playground->block.id != 255) 
				App->tiles->BlitText(App->playground->block.x, App->playground->block.y, Alive_Tetromino, NULL, App->playground->block, true);


			if (App->player->multiplayer)	//multiplayer enabled?
			{
				//Draw alive block (player 2)
				if (App->playground2->nextBlock.id != 255)
					App->tiles->BlitText2(304, 24, Alive_Tetromino, NULL, App->playground2->nextBlock, true);

				if (App->playground2->block.id != 255)
					App->tiles->BlitText2(App->playground2->block.x, App->playground2->block.y, Alive_Tetromino, NULL, App->playground2->block, true);
			}
		}
	}
	else
	{	
		isCurtainClosing = true;

		App->render->Blit(goTexture, 32, 0, NULL);
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}


	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->playground->Disable();

	LOG("Deleting background assets");

	App->textures->Unload(bgTexture);
	App->textures->Unload(goTexture);
	App->textures->Unload(curtainTexture);
	App->textures->Unload(lateralBars);
	App->textures->Unload(Russian1);
	App->textures->Unload(Russian2);
	App->textures->Unload(Russian3);

	App->tiles->UnLoad(Dead_Tetromino);
	App->tiles->UnLoad(Alive_Tetromino);

	return true;
}