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

	char Blocks_1[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\^_`abcdefghijklmnopqrstuvwxyz{|Ã}~!Á#$%&Â()*+À-./0123456789:;<=>?@ÇüéâäàåçêëèïîìÄÅÉæÆôöòûùÿÖÜø£Ø×ƒáíóúñÑªº¿®¬½¼¡«»" };
	Dead_Tetromino = App->tiles->Load("Assets/Sprites/tetromino_dead.png", Blocks_1, 10);
	
	char Blocks_2[] = { "abcdefghijklmnopqrstuvwxyz.," };
	Alive_Tetromino = App->tiles->Load("Assets/Sprites/tetromino_alive.png", Blocks_2, 7);


	newLevelFx = App->audio->LoadFx("Assets/audio/new_level.wav");
	blockAppearFx = App->audio->LoadFx("Assets/audio/block_appear.wav");
	bonusPointBarsFx = App->audio->LoadFx("Assets/audio/bonus_point_bars.wav");
	gameOverFx = App->audio->LoadFx("Assets/audio/game_over.wav");
	greatScoreFx = App->audio->LoadFx("Assets/audio/great_score.wav");
	hitFx = App->audio->LoadFx("Assets/audio/hit.wav");
	insertCoinFx = App->audio->LoadFx("Assets/audio/insert_coin.wav");
	lineFx = App->audio->LoadFx("Assets/audio/line.wav");
	roundCompletedFx = App->audio->LoadFx("Assets/audio/round_completed.wav");
	selectDiffFx = App->audio->LoadFx("Assets/audio/select_diff.wav");

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
		//Draw alive block
		if (App->playground->nextBlock.id != 255)
		{
			App->tiles->BlitText(8, 24, Alive_Tetromino, NULL, App->playground->nextBlock, true);
		}

		if (App->playground->block.id != 255) {

			App->tiles->BlitText(App->playground->block.x, App->playground->block.y, Alive_Tetromino, NULL, App->playground->block, true);
		}
	}
	else
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}


	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->playground->Disable();

	LOG("Deleting background assets");

	App->audio->UnloadFx();

	App->textures->Unload(bgTexture);

	return true;
}