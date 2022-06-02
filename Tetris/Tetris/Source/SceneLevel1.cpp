#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayGround.h"
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
}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	curtainClosing.Reset();
	curtainOpening.Reset();

	bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_1.png");
	lateralNumbersTexture = App->textures->Load("Assets/Sprites/lateralNumbers_BG_1.png");
	goTexture = App->textures->Load("Assets/Sprites/gameover.png");
	curtainTexture = App->textures->Load("Assets/Sprites/sprites_courtin.png");
	lateralBars = App->textures->Load("Assets/Sprites/lateralBars.png");

	char Blocks_1[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ[^_`abcdefghijklmnopqrstuvwxyz{|Ã}~!Á#$%&Â()*+À-./0123456789:;<=>?@ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜø£Ø×ƒáíóúñÑªº¿®¬½¼¡«»»»»»»»»»»" };
	Dead_Tetromino = App->tiles->Load("Assets/Sprites/tetromino_dead.png", Blocks_1, 10);
	
	char Blocks_2[] = { "abcdefghijklmnopqrstuvwxyz.," };
	Alive_Tetromino = App->tiles->Load("Assets/Sprites/tetromino_alive.png", Blocks_2, 7);

	//App->audio->PlayMusic("Assets/audio/1_Loginska.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->playground->Enable();

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
	if(App->player->stateWin || App->player->stateLose){ curtainClosing.Update(); }
	if (App->player->stateStartLevel) { curtainOpening.Update(); }
	lateralBarsAnim.Update();
	lateralBarCounter++;
	

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

	//Next block
	if (App->playground->nextBlock.id != 255)
	{
		App->tiles->BlitText(8, 24, Alive_Tetromino, NULL, App->playground->nextBlock, true);
	}

	
	if (App->player->stateStartLevel) {
		//CURTAIN ANIMATION OPENING
		App->render->Blit(curtainTexture, 128, 96, &(curtainOpening.GetCurrentFrame()));
	}
	
	if (App->player->statePlay || App->player->stateLine) {

		if (!playMusic) {
			App->audio->PlayMusic("Assets/audio/1_Loginska.ogg", 1.0f);
			playMusic = true;
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

		//Draw dead blocks
		for (size_t i = 0; i < 23; i++)
		{
			for (size_t j = 0; j < 12; j++)
			{
				if (playground[i][j] != 0 && playground[i][j] != 255)
				{
					App->tiles->BlitText(j, i, Dead_Tetromino, playground[i][j], App->playground->block, false);

				}
			}
		}

		//draw lateral numbers (5 to 1)
		if (levelLines == 5)
		{
			lateralNumbersSection.x = 0; lateralNumbersSection.y = 0;
			lateralNumbersSection.w = 16; lateralNumbersSection.h = 16;
			App->render->Blit(lateralNumbersTexture, 4, 68, &lateralNumbersSection);
		}
		else if (levelLines == 4)
		{
			lateralNumbersSection.x = 16; lateralNumbersSection.y = 0;
			lateralNumbersSection.w = 16; lateralNumbersSection.h = 16;
			App->render->Blit(lateralNumbersTexture, 4, 95, &lateralNumbersSection);
		}
		else if (levelLines == 3)
		{
			lateralNumbersSection.x = 32; lateralNumbersSection.y = 0;
			lateralNumbersSection.w = 16; lateralNumbersSection.h = 16;
			App->render->Blit(lateralNumbersTexture, 4, 122, &lateralNumbersSection);
		}
		else if (levelLines == 2)
		{
			lateralNumbersSection.x = 48; lateralNumbersSection.y = 0;
			lateralNumbersSection.w = 16; lateralNumbersSection.h = 16;
			App->render->Blit(lateralNumbersTexture, 4, 149, &lateralNumbersSection);
		}
		else if (levelLines == 1)
		{
			lateralNumbersSection.x = 64; lateralNumbersSection.y = 0;
			lateralNumbersSection.w = 16; lateralNumbersSection.h = 16;
			App->render->Blit(lateralNumbersTexture, 4, 176, &lateralNumbersSection);
		}



		if (App->playground->gameOver == false)
		{
			if (levelLines <= 0 && App->playground->lineLimit == false && App->player->statePlay == true) {
				//WIN
				App->player->stateWin = true;
				App->player->statePlay = false;
			}
			else {
				//Draw alive block

				if (App->playground->block.id != 255) {

					App->tiles->BlitText(App->playground->block.x, App->playground->block.y, Alive_Tetromino, NULL, App->playground->block, true);
				}
			}
		}
		else
		{
			//Game Over
			App->player->stateLose = true;
			App->player->statePlay = false;
		}
	}

	if (App->player->stateLose == true) {
		//Game Over

		if (playMusic) {
			App->audio->PlayMusic("", 1.0f);
			playMusic = false;
		}

		//CURTAIN ANIMATION CLOSING  NOO VA :(
		App->render->Blit(curtainTexture, 128, 96, &(curtainClosing.GetCurrentFrame()));

		App->render->Blit(goTexture, 32, 0, NULL);

		if (winDelay <= 0) {
			//App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		}
		winDelay--;
	}

	if (App->player->stateWin == true) {
		//WIN

		if (playMusic) {
			App->audio->PlayMusic("", 1.0f);
			playMusic = false;
		}

		//CURTAIN ANIMATION CLOSING  NOO VA :(
		App->render->Blit(curtainTexture, 128, 96, &(curtainClosing.GetCurrentFrame()));

		if (winDelay<=0) {
			//App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		}
		winDelay--;
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

	App->tiles->UnLoad(Dead_Tetromino);
	App->tiles->UnLoad(Alive_Tetromino);

	return true;
}