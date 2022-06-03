#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleData.h"
#include "SceneLevel1.h"
#include "ModulePlayGround.h"
#include "ModulePlayGround2.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	
	destroyed = false;
	
	bool stateStartLevel = true;
	bool stateWin = false;
	bool stateLose = false;

	bool stateLine1 = false;
	bool stateLine2 = false;
	bool statePlay1 = false;
	bool statePlay2 = false;

	//bool multiplayer = false;

	score = 000;
	totalLines = 000;
	round = 000;

	char lookupTable[] = { "abcdefghijklmnopqrstuvwxyz 0123456789.,;:$#'! /?%&()@ " };
	Tetris_font_black = App->fonts->Load("Assets/Fonts/sprite_font_black.png", lookupTable, 6);
	Tetris_font_blue = App->fonts->Load("Assets/Fonts/sprite_font_blue.png", lookupTable, 6);
	Tetris_font_brown = App->fonts->Load("Assets/Fonts/sprite_font_brown.png", lookupTable, 6);
	Tetris_font_darkblue = App->fonts->Load("Assets/Fonts/sprite_font_darkblue.png", lookupTable, 6);
	Tetris_font_lightblue = App->fonts->Load("Assets/Fonts/sprite_font_lightblue).png", lookupTable, 6);
	Tetris_font_purpura = App->fonts->Load("Assets/Fonts/sprite_font_purpura.png", lookupTable, 6);
	Tetris_font_red = App->fonts->Load("Assets/Fonts/sprite_font_red.png", lookupTable, 6);
	Tetris_font_white = App->fonts->Load("Assets/Fonts/sprite_font_white.png", lookupTable, 6);

	rainbowBar = App->textures->Load("Assets/Sprites/rainbowBar.png");

	return ret;
}

Update_Status ModulePlayer::Update()
{

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed){}

	if (score > App->data->high_score) {
		App->data->high_score = score;
	}

	//Draw rainbow bar
	if (totalLines >= 36)
	{
		rainbow = 10;
		App->render->Blit(rainbowBar, 8, 214);
	}
	else if (totalLines >= 32)
	{
		rainbow = 9;
		rainbowBarSection = { 0,2,8,2 };
		App->render->Blit(rainbowBar, 8, 216, &rainbowBarSection);
	}
	else if (totalLines >= 28)
	{
		rainbow = 8;
		rainbowBarSection = { 0,4,8,2 };
		App->render->Blit(rainbowBar, 8, 218, &rainbowBarSection);
	}
	else if (totalLines >= 24)
	{
		rainbow = 7;
		rainbowBarSection = { 0,6,8,2 };
		App->render->Blit(rainbowBar, 8, 220, &rainbowBarSection);
	}
	else if (totalLines >= 20)
	{
		rainbow = 6;
		rainbowBarSection = { 0,8,8,2 };
		App->render->Blit(rainbowBar, 8, 222, &rainbowBarSection);
	}
	else if (totalLines >= 16)
	{
		rainbow = 5;
		rainbowBarSection = { 0,10,8,2 };
		App->render->Blit(rainbowBar, 8, 224, &rainbowBarSection);
	}
	else if (totalLines >= 12)
	{
		rainbow = 4;
		rainbowBarSection = { 0,12,8,2 };
		App->render->Blit(rainbowBar, 8, 226, &rainbowBarSection);
	}
	else if (totalLines >= 8)
	{
		rainbow = 3;
		rainbowBarSection = { 0,14,8,2 };
		App->render->Blit(rainbowBar, 8, 228, &rainbowBarSection);
	}
	else if (totalLines >= 4)
	{
		rainbow = 2;
		rainbowBarSection = {0,16,8,2};
		App->render->Blit(rainbowBar, 8,230, &rainbowBarSection);
	}


	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->BlitText(25, 217, Tetris_font_red, "score");
	App->fonts->BlitText(65, 217, Tetris_font_red, scoreText);

	sprintf_s(linesText, 10, "%7d", totalLines);
	App->fonts->BlitText(25, 225, Tetris_font_red, "lines");
	App->fonts->BlitText(65, 225, Tetris_font_red, linesText);

	sprintf_s(roundText, 10, "%7d", totalLines);
	App->fonts->BlitText(130, 210, Tetris_font_darkblue, "lines");
	App->fonts->BlitText(153, 210, Tetris_font_darkblue, linesText);

	sprintf_s(high_scoreText, 10, "%7d", App->data->high_score);
	App->fonts->BlitText(130, 185, Tetris_font_darkblue, "high score");
	App->fonts->BlitText(153, 195, Tetris_font_darkblue, high_scoreText);

	sprintf_s(creditsText, 10, "%7d", credits);
	App->fonts->BlitText(130, 226, Tetris_font_darkblue, "credits");
	App->fonts->BlitText(153, 226, Tetris_font_darkblue, creditsText);

	//Text
	App->fonts->BlitText(240, 60, Tetris_font_white, "stats");
	App->fonts->BlitText(8, 8, Tetris_font_red, "next");

	timer++;
	if (timer == 240) { timer = 0; }

	if (timer<120) {
		App->fonts->BlitText(230, 216, Tetris_font_lightblue, "join in");
		App->fonts->BlitText(230, 224, Tetris_font_lightblue, "any time");
	}

	if (timer>=120) {
		App->fonts->BlitText(237, 216, Tetris_font_lightblue, "insert");
		App->fonts->BlitText(246, 224, Tetris_font_lightblue, "coin");
	}


	//Middle screen (Objectives)
	if (!multiplayer && (statePlay1 || stateLine1)) {
		if (App->sceneLevel_1->levelLines < 10) { sprintf_s(linesLeftText, 10, "0%d", App->sceneLevel_1->levelLines); }
		else { sprintf_s(linesLeftText, 10, "%d", App->sceneLevel_1->levelLines); }
		App->fonts->BlitText(150, 130, Tetris_font_white, "lines");
		App->fonts->BlitText(150, 146, Tetris_font_white, "left");
		App->fonts->BlitText(135, 115, Tetris_font_red, linesLeftText);
	}

	if (stateStartLevel) {
		if (delayStart <= 0) {
			if (App->sceneLevel_1->levelLines < 10) { sprintf_s(linesLeftText, 10, "0%d", App->sceneLevel_1->levelLines); }
			else { sprintf_s(linesLeftText, 10, "%d", App->sceneLevel_1->levelLines); }
			App->fonts->BlitText(137, 106, Tetris_font_white, "complete");
			App->fonts->BlitText(137, 121, Tetris_font_white, linesLeftText);
			App->fonts->BlitText(161, 121, Tetris_font_white, "lines");
			App->fonts->BlitText(137, 136, Tetris_font_white, "to go to");
			App->fonts->BlitText(128, 153, Tetris_font_white, "next round");
		}

		delayStart--;

		if (delayStart <= -80) {
			stateStartLevel = false;
			statePlay1 = true;
			App->playground->NextBlock();
			if (multiplayer) {
				statePlay2 = true;
				App->playground2->NextBlock();
			}
			delayStart = 40;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}


bool ModulePlayer::CleanUp()
{
	LOG("Deleting background assets");

	App->fonts->UnLoad(Tetris_font_black);
	App->fonts->UnLoad(Tetris_font_blue);
	App->fonts->UnLoad(Tetris_font_brown);
	App->fonts->UnLoad(Tetris_font_darkblue);
	App->fonts->UnLoad(Tetris_font_lightblue);
	App->fonts->UnLoad(Tetris_font_purpura);
	App->fonts->UnLoad(Tetris_font_red);
	App->fonts->UnLoad(Tetris_font_white);

	App->textures->Unload(rainbowBar);

	return true;
}
