#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

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
	score = 000;
	lines = 000;
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

	return ret;
}

Update_Status ModulePlayer::Update()
{

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{

	}

	score += 1;

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->BlitText(23, 216, Tetris_font_red, "score");
	App->fonts->BlitText(50, 216, Tetris_font_red, scoreText);

	sprintf_s(linesText, 10, "%7d", lines);
	App->fonts->BlitText(23, 224, Tetris_font_red, "lines");
	App->fonts->BlitText(50, 224, Tetris_font_red, linesText);

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

	return true;
}
