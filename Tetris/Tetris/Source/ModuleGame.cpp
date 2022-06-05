#include "ModuleGame.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleData.h"
#include "SceneGame.h"
#include "ModulePlayGround.h"
#include "ModulePlayGround2.h"

#include <stdio.h>

ModuleGame::ModuleGame(bool startEnabled) : Module(startEnabled)
{
	
}

ModuleGame::~ModuleGame()
{

}

bool ModuleGame::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	
	destroyed = false;
	
	stateStartLevel = true;
	stateWin = false;
	stateLose = false;

	stateLine1 = false;
	stateLine2 = false;
	statePlay1 = false;
	statePlay2 = false;
	stateEndMultiplayer = false;

	//bool multiplayer = false;

	scorePlayer1 = 000;
	totalLines = 000;
	scorePlayer2 = 000;
	totalLinesPlayer2 = 000;
	round = 000;

	char lookupTable[] = { "abcdefghijklmnopqrstuvwxyz 0123456789.,;:$#'! /?%&()@ " };
	Tetris_font_black = App->fonts->Load("Assets/Fonts/sprite_font_black.png", lookupTable, 6);
	Tetris_font_blue = App->fonts->Load("Assets/Fonts/sprite_font_blue.png", lookupTable, 6);
	Tetris_font_brown = App->fonts->Load("Assets/Fonts/sprite_font_brown.png", lookupTable, 6);
	Tetris_font_darkblue = App->fonts->Load("Assets/Fonts/sprite_font_darkblue.png", lookupTable, 6);
	Tetris_font_lightblue = App->fonts->Load("Assets/Fonts/sprite_font_lightblue.png", lookupTable, 6);
	Tetris_font_purpura = App->fonts->Load("Assets/Fonts/sprite_font_purpura.png", lookupTable, 6);
	Tetris_font_red = App->fonts->Load("Assets/Fonts/sprite_font_red.png", lookupTable, 6);
	Tetris_font_white = App->fonts->Load("Assets/Fonts/sprite_font_white.png", lookupTable, 6);

	rainbowBar = App->textures->Load("Assets/Sprites/rainbowBar.png");

	return ret;
}

Update_Status ModuleGame::Update()
{

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleGame::PostUpdate()
{
	if (!destroyed){} //Huevo de verano

	if (scorePlayer1 > App->data->high_score) {
		App->data->high_score = scorePlayer1;
	}
	if (multiplayer) {
		if (scorePlayer1 > App->data->high_score_multiplayer) {
			App->data->high_score_multiplayer = scorePlayer1;
		}
		if (scorePlayer2 > App->data->high_score_multiplayer) {
			App->data->high_score_multiplayer = scorePlayer2;
		}
	}

	//Draw rainbow bar Player 1
	if (totalLines >= 36)
	{
		rainbow = 10;
		App->render->Blit(rainbowBar, 8, 214);
	}
	if (totalLines >= 32)
	{
		rainbow = 9;
		rainbowBarSection = { 0,2,8,2 };
		App->render->Blit(rainbowBar, 8, 216, &rainbowBarSection);
	}
	if (totalLines >= 28)
	{
		rainbow = 8;
		rainbowBarSection = { 0,4,8,2 };
		App->render->Blit(rainbowBar, 8, 218, &rainbowBarSection);
	}
	if (totalLines >= 24)
	{
		rainbow = 7;
		rainbowBarSection = { 0,6,8,2 };
		App->render->Blit(rainbowBar, 8, 220, &rainbowBarSection);
	}
	if (totalLines >= 20)
	{
		rainbow = 6;
		rainbowBarSection = { 0,8,8,2 };
		App->render->Blit(rainbowBar, 8, 222, &rainbowBarSection);
	}
	if (totalLines >= 16)
	{
		rainbow = 5;
		rainbowBarSection = { 0,10,8,2 };
		App->render->Blit(rainbowBar, 8, 224, &rainbowBarSection);
	}
	if (totalLines >= 12)
	{
		rainbow = 4;
		rainbowBarSection = { 0,12,8,2 };
		App->render->Blit(rainbowBar, 8, 226, &rainbowBarSection);
	}
	if (totalLines >= 8)
	{
		rainbow = 3;
		rainbowBarSection = { 0,14,8,2 };
		App->render->Blit(rainbowBar, 8, 228, &rainbowBarSection);
	}
	if (totalLines >= 4)
	{
		rainbow = 2;
		rainbowBarSection = {0,16,8,2};
		App->render->Blit(rainbowBar, 8,230, &rainbowBarSection);
	}

	//Draw rainbow bar Player 2
	if (totalLinesPlayer2 >= 36)
	{
		rainbow = 10;
		App->render->Blit(rainbowBar, 320, 214);
	}
	if (totalLinesPlayer2 >= 32)
	{
		rainbow = 9;
		rainbowBarSection = { 0,2,8,2 };
		App->render->Blit(rainbowBar, 320, 216, &rainbowBarSection);
	}
	if (totalLinesPlayer2 >= 28)
	{
		rainbow = 8;
		rainbowBarSection = { 0,4,8,2 };
		App->render->Blit(rainbowBar, 320, 218, &rainbowBarSection);
	}
	if (totalLinesPlayer2 >= 24)
	{
		rainbow = 7;
		rainbowBarSection = { 0,6,8,2 };
		App->render->Blit(rainbowBar, 320, 220, &rainbowBarSection);
	}
	if (totalLinesPlayer2 >= 20)
	{
		rainbow = 6;
		rainbowBarSection = { 0,8,8,2 };
		App->render->Blit(rainbowBar, 320, 222, &rainbowBarSection);
	}
	if (totalLinesPlayer2 >= 16)
	{
		rainbow = 5;
		rainbowBarSection = { 0,10,8,2 };
		App->render->Blit(rainbowBar, 320, 224, &rainbowBarSection);
	}
	if (totalLinesPlayer2 >= 12)
	{
		rainbow = 4;
		rainbowBarSection = { 0,12,8,2 };
		App->render->Blit(rainbowBar, 320, 226, &rainbowBarSection);
	}
	if (totalLinesPlayer2 >= 8)
	{
		rainbow = 3;
		rainbowBarSection = { 0,14,8,2 };
		App->render->Blit(rainbowBar, 320, 228, &rainbowBarSection);
	}
	if (totalLinesPlayer2 >= 4)
	{
		rainbow = 2;
		rainbowBarSection = { 0,16,8,2 };
		App->render->Blit(rainbowBar, 320, 230, &rainbowBarSection);
	}


	// Draw UI --------------------------------------

	//Player 1 score
	sprintf_s(scoreTextPlayer1, 10, "%7d", scorePlayer1);
	App->fonts->BlitText(25, 217, Tetris_font_red, "score");
	App->fonts->BlitText(65, 217, Tetris_font_red, scoreTextPlayer1);

	sprintf_s(linesText, 10, "%7d", totalLines);
	App->fonts->BlitText(25, 225, Tetris_font_red, "lines");
	App->fonts->BlitText(65, 225, Tetris_font_red, linesText);

	if (!multiplayer) //Singleplayer UI
	{
		//Game data middle
		sprintf_s(high_scoreText, 10, "%7d", App->data->high_score);
		App->fonts->BlitText(130, 185, fontMiddle, "high score");
		App->fonts->BlitText(153, 195, fontMiddle, high_scoreText);

		sprintf_s(roundText, 10, "%7d", (App->sceneGame->currentLevel) + 1);
		App->fonts->BlitText(130, 210, fontMiddle, "round");
		App->fonts->BlitText(153, 210, fontMiddle, roundText);

		sprintf_s(creditsText, 10, "%7d", credits);
		App->fonts->BlitText(130, 226, fontMiddle, "credits");
		App->fonts->BlitText(153, 226, fontMiddle, creditsText);

		//Text right
		App->fonts->BlitText(240, 60, Tetris_font_white, "stats");

		timer++;
		if (timer == 240) { timer = 0; }

		if (timer < 120) {
			App->fonts->BlitText(230, 217, fontRight, "join in");
			App->fonts->BlitText(230, 225, fontRight, "any time");
		}

		if (timer >= 120) {
			App->fonts->BlitText(237, 217, fontRight, "insert");
			App->fonts->BlitText(245, 225, fontRight, "coin");
		}
	}
	else //Multiplayer UI
	{
		//Player 2 score
		sprintf_s(scoreTextPlayer2, 10, "%7d", scorePlayer2);
		App->fonts->BlitText(217, 217, Tetris_font_red, "score");
		App->fonts->BlitText(257, 217, Tetris_font_red, scoreTextPlayer2);

		sprintf_s(linesTextPlayer2, 10, "%7d", totalLinesPlayer2);
		App->fonts->BlitText(217, 225, Tetris_font_red, "lines");
		App->fonts->BlitText(257, 225, Tetris_font_red, linesTextPlayer2);

		App->fonts->BlitText(296, 8, Tetris_font_red, "next");

		//Game data middle
		sprintf_s(high_scoreText, 10, "%7d", App->data->high_score_multiplayer);
		App->fonts->BlitText(130, 185, Tetris_font_darkblue, "high score");
		App->fonts->BlitText(153, 195, Tetris_font_darkblue, high_scoreText);

		sprintf_s(creditsText, 10, "%7d", credits);
		App->fonts->BlitText(130, 226, Tetris_font_darkblue, "credits");
		App->fonts->BlitText(153, 226, Tetris_font_darkblue, creditsText);
	}
	App->fonts->BlitText(8, 8, Tetris_font_red, "next");

	


	//Middle screen (Objectives)
	if (!multiplayer && (statePlay1 || stateLine1)) {
		if (App->sceneGame->levelLines < 10) { sprintf_s(linesLeftText, 10, "0%d", App->sceneGame->levelLines); }
		else { sprintf_s(linesLeftText, 10, "%d", App->sceneGame->levelLines); }
		App->fonts->BlitText(150, 130, Tetris_font_white, "lines");
		App->fonts->BlitText(150, 146, Tetris_font_white, "left");
		App->fonts->BlitText(135, 115, Tetris_font_red, linesLeftText);
	}

	if (!multiplayer && stateStartLevel) {
		if (delayStart <= 0) {
			if (App->sceneGame->levelLines < 10) { sprintf_s(linesLeftText, 10, "0%d", App->sceneGame->levelLines); }
			else { sprintf_s(linesLeftText, 10, "%d", App->sceneGame->levelLines); }
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

	if (multiplayer && stateStartLevel) {
		if (delayStart <= 0) {
			if (App->sceneGame->levelLines < 10) { sprintf_s(linesLeftText, 10, "0%d", App->sceneGame->levelLines); }
			else { sprintf_s(linesLeftText, 10, "%d", App->sceneGame->levelLines); }
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

	if (!multiplayer && stateWin) {
		if (App->sceneGame->winDelay > 60) {
			App->fonts->BlitText(152, 121, Tetris_font_white, "you");
			App->fonts->BlitText(142, 136, Tetris_font_white, "did it");
		}
		else if (App->sceneGame->winDelay > 0) {
			App->fonts->BlitText(135, 106, Tetris_font_white, "bonus for");
			App->fonts->BlitText(151, 115, Tetris_font_white, "low");
			App->fonts->BlitText(143, 124, Tetris_font_white, "puzzle");
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}


bool ModuleGame::CleanUp()
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
