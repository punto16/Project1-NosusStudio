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
	stateLine = false;
	statePlay = false;
	stateStartLevel = true;
	stateWin = false;
	stateLose = false;

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
	if (statePlay || stateLine) {
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
			statePlay = true;
			App->playground->NextBlock();
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
