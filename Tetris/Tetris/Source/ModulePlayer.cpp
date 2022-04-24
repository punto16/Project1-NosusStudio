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

	char lookupTable[] = { "abcdefghijklmnopqrstuvwxyz 0123456789.,;:$#'! /?%&()@ " };
	Tetris_font_black = App->fonts->Load("Assets/Fonts/Tetris_font_black.png", lookupTable, 6);

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

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	App->fonts->BlitText(23, 216, Tetris_font_black, "score");
	//App->fonts->BlitText(58, 228, scoreFont, scoreText);
	App->fonts->BlitText(23, 224, Tetris_font_black, "lines");
	//App->fonts->BlitText(58, 228, scoreFont, LevelText);

	return Update_Status::UPDATE_CONTINUE;
}

