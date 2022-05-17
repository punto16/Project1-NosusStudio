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

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_1.png");
	goTexture = App->textures->Load("Assets/Sprites/gameover.png");

	char Blocks_1[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ[^_`abcdefghijklmnopqrstuvwxyz{|Ã}~!Á#$%&Â()*+À-./0123456789:;<=>?@ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜø£Ø×ƒáíóúñÑªº¿®¬½¼¡«»»»»»»»»»»" };
	Dead_Tetromino = App->tiles->Load("Assets/Sprites/tetromino_dead.png", Blocks_1, 10);
	
	char Blocks_2[] = { "abcdefghijklmnopqrstuvwxyz.," };
	Alive_Tetromino = App->tiles->Load("Assets/Sprites/tetromino_alive.png", Blocks_2, 7);


	

	App->audio->PlayMusic("Assets/audio/1_Loginska.ogg", 1.0f);

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
	lines = 5;

	return ret;
}

Update_Status SceneLevel1::Update()
{
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

	if (App->playground->gameOver == false)
	{
		if (lines <= 0) {
			App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		}
		else {
			//Draw alive block
			if (App->playground->nextBlock.id != 255)
			{
				App->tiles->BlitText(8, 24, Alive_Tetromino, NULL, App->playground->nextBlock, true);
			}

			if (App->playground->block.id != 255) {

				App->tiles->BlitText(App->playground->block.x, App->playground->block.y, Alive_Tetromino, NULL, App->playground->block, true);
			}
		}
	}
	else
	{
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

	return true;
}