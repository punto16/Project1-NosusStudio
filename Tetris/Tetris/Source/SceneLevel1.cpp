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

	char Blocks[] = { "ab  cdefghijklmnop  qr  s   " };
	Alive_Tetromino = App->fonts->Load("Assets/Sprites/tetromino_alive.png", Blocks, 7);


	/*
	App->audio->LoadFx("Assets/audio/block_appear.wav");
	App->audio->LoadFx("Assets/audio/bonus_point_bars.wav");
	App->audio->LoadFx("Assets/audio/game_over.wav");
	App->audio->LoadFx("Assets/audio/great_score.wav");
	App->audio->LoadFx("Assets/audio/hit.wav");
	App->audio->LoadFx("Assets/audio/insert_coin.wav");
	App->audio->LoadFx("Assets/audio/line.wav");
	App->audio->LoadFx("Assets/audio/new_level.wav");
	App->audio->LoadFx("Assets/audio/round_completed.wav");
	App->audio->LoadFx("Assets/audio/select_diff.wav");
	*/

	App->audio->PlayMusic("Assets/audio/1_Loginska.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->playground->Enable();

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

	//Draw alive block
	if (App->playground->block.id != 255) {
		blockText = App->playground->block.id + App->playground->block.rotation;

		blockText_text[0] = Dictionary[blockText];
		int x = (App->playground->block.x * 8) + 32;
		int y = (App->playground->block.y * 8) + 24;

		App->fonts->BlitText(x, y, Alive_Tetromino, blockText_text);
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

char SceneLevel1::PlayGroundGetter(int i, int j)
{
	return playground[i][j];
}

int SceneLevel1:: linesofLevelGetter()
{
	return lines;
}
