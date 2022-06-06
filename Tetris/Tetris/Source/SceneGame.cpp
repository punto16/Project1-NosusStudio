#include "SceneGame.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleGame.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayGround.h"
#include "ModulePlayGround2.h"
#include "ModuleFonts.h"
#include "ModuleTiles.h"

SceneGame::SceneGame(bool startEnabled) : Module(startEnabled)
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

SceneGame::~SceneGame()
{

}

// Load assets
bool SceneGame::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	curtainClosing.Reset();
	curtainOpening.Reset();

	bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_1.png");
	lateralNumbersTexture = App->textures->Load("Assets/Sprites/lateralNumbers_BG_1.png");
	lateralNumbersBlink = App->textures->Load("Assets/Sprites/lateralNumbers_white.png");
	goTexture = App->textures->Load("Assets/Sprites/gameover.png");
	curtainTexture = App->textures->Load("Assets/Sprites/sprites_courtin.png");
	lateralBars = App->textures->Load("Assets/Sprites/lateralBars.png");
  
	//App->audio->PlayMusic("Assets/audio/1_Loginska.ogg", 1.0f);
  
	Russian1 = App->textures->Load("Assets/Sprites/Dance1");
	Russian2 = App->textures->Load("Assets/Sprites/Dance2");
	Russian3 = App->textures->Load("Assets/Sprites/Dance3");
  
	Dead_Tetromino = App->tiles->Load("Assets/Sprites/tetromino_dead.png", 15, 10);
	
	Alive_Tetromino = App->tiles->Load("Assets/Sprites/tetromino_alive.png", 4, 7);
  
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->game->Enable();
	App->playground->Enable();

	if (App->game->multiplayer == true)
		App->playground2->Enable();

	for (size_t i = 0; i < 23; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			if (playground[i][j] != 255)
				playground[i][j] = 0;
		}
	}

	for (size_t i = 0; i < 23; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			if (playground2[i][j] != 255)
				playground2[i][j] = 0;
		}
	}

	App->playground->gameOver = false;
	if (App->game->multiplayer) { App->playground2->gameOver = false; }

	winDelay = 240;
	loseDelay = 120;

	App->playground->bonusPoints = 10;
	App->playground->bonus = false;
	App->playground->lastBonus = 2;
	
	levelLines = levelsTotalLines[currentLevel];

	if (currentLevel >= 0 && currentLevel < 3) {
		bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_1.png");
		App->game->fontMiddle = App->game->Tetris_font_darkblue;
		App->game->fontRight = App->game->Tetris_font_lightblue;
		App->game->fontScore = App->game->Tetris_font_darkblue;
	}
	else if (currentLevel >= 3 && currentLevel < 6) {
		bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_2.png");
		App->game->fontMiddle = App->game->Tetris_font_purpura;
		App->game->fontRight = App->game->Tetris_font_blue;
		App->game->fontScore = App->game->Tetris_font_purpura;
	}
	else if (currentLevel >= 6 && currentLevel < 9) {
		bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_3.png");
		App->game->fontMiddle = App->game->Tetris_font_lightblue;
		App->game->fontRight = App->game->Tetris_font_lightblue;
		App->game->fontScore = App->game->Tetris_font_brown;
	}
	else if (currentLevel >= 9 && currentLevel < 12) {
		bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_1.png");
		App->game->fontMiddle = App->game->Tetris_font_darkblue;
		App->game->fontRight = App->game->Tetris_font_lightblue;
		App->game->fontScore = App->game->Tetris_font_darkblue;
	}

	return ret;
}

void SceneGame::ResetLevel()
{
	currentLevel++;
	levelLines = levelsTotalLines[currentLevel];

	App->playground->nextBlock.id = App->playground->RandomBlock();
	
	App->playground->lineLimit = false;
	App->playground->selectBlock = false;

	App->playground->lineLimit = false;

	if (currentLevel < 3) {
		bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_1.png");
		App->game->fontMiddle = App->game->Tetris_font_darkblue;
		App->game->fontRight = App->game->Tetris_font_lightblue;
		App->game->fontScore = App->game->Tetris_font_darkblue;
	}
	else if (currentLevel < 6) {
		bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_2.png");
		App->game->fontMiddle = App->game->Tetris_font_purpura;
		App->game->fontRight = App->game->Tetris_font_blue;
		App->game->fontScore = App->game->Tetris_font_purpura;
	}
	else if (currentLevel < 9) {
		bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_3.png");
		App->game->fontMiddle = App->game->Tetris_font_lightblue;
		App->game->fontRight = App->game->Tetris_font_lightblue;
		App->game->fontScore = App->game->Tetris_font_brown;
	}
	else if (currentLevel < 12) {
		bgTexture = App->textures->Load("Assets/Sprites/Tetris_BG_1.png");
		App->game->fontMiddle = App->game->Tetris_font_darkblue;
		App->game->fontRight = App->game->Tetris_font_lightblue;
		App->game->fontScore = App->game->Tetris_font_darkblue;
	}


	//Initial blocks (lvl 4-6)
	if (currentLevel == 4)
	{
		for (size_t i = 0; i < 23; i++)
		{
			for (size_t j = 0; j < 12; j++)
				playground[i][j] = level4[i][j];
		}
	}
	else if (currentLevel == 5)
	{
		for (size_t i = 0; i < 23; i++)
		{
			for (size_t j = 0; j < 12; j++)
				playground[i][j] = level5[i][j];
		}
	}
	else if (currentLevel == 5)
	{
		for (size_t i = 0; i < 23; i++)
		{
			for (size_t j = 0; j < 12; j++)
				playground[i][j] = level6[i][j];
		}
	}
	else
	{
		for (size_t i = 0; i < 23; i++)
		{
			for (size_t j = 0; j < 12; j++)
			{
				if (playground[i][j] != 255)
					playground[i][j] = 0;
			}
		}
	}


	App->playground->gameOver = false;

	winDelay = 240;
	loseDelay = 120;

	App->playground->bonusPoints = 10;
	App->playground->bonus = false;
	App->playground->lastBonus = 2;

	curtainClosing.Reset();
	curtainOpening.Reset();

	App->game->destroyed = false;
	
	App->game->stateStartLevel = true;
	App->game->stateWin = false;
	App->game->stateLose = false;

	App->game->stateLine1 = false;
	App->game->stateLine2 = false;
	App->game->statePlay1 = false;
	App->game->statePlay2 = false;
	App->game->stateEndMultiplayer = false;
}

Update_Status SceneGame::Update()
{
	if(App->game->stateLose || App->game->stateEndMultiplayer){ curtainClosing.Update(); }
	if (winDelay <= 0) { curtainClosing.Update(); }
	if (App->game->stateStartLevel) { curtainOpening.Update(); }
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
Update_Status SceneGame::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	//Next block (player 1)
	if (App->playground->nextBlock.id != 255)
	{
		App->tiles->BlitText(8, 24, Alive_Tetromino, NULL, App->playground->nextBlock, true);
	}

	//Next block (player 2)
	if (App->playground2->nextBlock.id != 255 && App->game->multiplayer)
	{
		App->tiles->BlitText2(304, 24, Alive_Tetromino, NULL, App->playground2->nextBlock, true);
	}
	
	if (App->game->stateStartLevel) {
		//CURTAIN ANIMATION OPENING
		App->render->Blit(curtainTexture, 128, 96, &(curtainOpening.GetCurrentFrame()));
	}
	
	if (!App->game->multiplayer && (App->game->statePlay1 || App->game->stateLine1)) {

		if (!playMusic) {
			if (currentLevel == 0 || currentLevel ==4 || currentLevel == 8) {
				App->audio->PlayMusic("Assets/audio/1_Loginska.ogg", 1.0f);
			}
			else if (currentLevel == 1 || currentLevel == 5 || currentLevel == 9) {
				App->audio->PlayMusic("Assets/audio/2_Bradinsky.ogg", 1.0f);
			}
			else if (currentLevel == 2 || currentLevel == 6 || currentLevel == 10) {
				App->audio->PlayMusic("Assets/audio/3_Karinka.ogg", 1.0f);
			}
			else if (currentLevel == 3 || currentLevel == 7 || currentLevel == 11) {
				App->audio->PlayMusic("Assets/audio/4_Troika.ogg", 1.0f);
			}
			playMusic = true;
		}

		if (App->playground->lines == 4) // lateral bars
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

		//draw lateral numbers (5 to 1)
		if (levelLines == 5)
		{
			lateralNumbersSection.x = 0; lateralNumbersSection.y = 0;
			lateralNumbersSection.w = 16; lateralNumbersSection.h = 16;
			if (numberBlink < 2 && App->game->stateLine1)
			{
				App->render->Blit(lateralNumbersBlink, 4, 68, &lateralNumbersSection);
			}
			else
			{
				App->render->Blit(lateralNumbersTexture, 4, 68, &lateralNumbersSection);
			}

		}
		else if (levelLines == 4)
		{
			lateralNumbersSection.x = 16; lateralNumbersSection.y = 0;
			lateralNumbersSection.w = 16; lateralNumbersSection.h = 16;

			if (numberBlink < 2 && App->game->stateLine1)
			{
				App->render->Blit(lateralNumbersBlink, 4, 95, &lateralNumbersSection);
			}
			else
			{
				App->render->Blit(lateralNumbersTexture, 4, 95, &lateralNumbersSection);
			}
		}
		else if (levelLines == 3)
		{
			lateralNumbersSection.x = 32; lateralNumbersSection.y = 0;
			lateralNumbersSection.w = 16; lateralNumbersSection.h = 16;

			if (numberBlink < 2 && App->game->stateLine1)
			{
				App->render->Blit(lateralNumbersBlink, 4, 122, &lateralNumbersSection);
			}
			else
			{
				App->render->Blit(lateralNumbersTexture, 4, 122, &lateralNumbersSection);
			}

		}
		else if (levelLines == 2)
		{
			lateralNumbersSection.x = 48; lateralNumbersSection.y = 0;
			lateralNumbersSection.w = 16; lateralNumbersSection.h = 16;

			if (numberBlink < 2 && App->game->stateLine1)
			{
				App->render->Blit(lateralNumbersBlink, 4, 149, &lateralNumbersSection);
			}
			else
			{
				App->render->Blit(lateralNumbersTexture, 4, 149, &lateralNumbersSection);
			}
		}
		else if (levelLines == 1)
		{
			lateralNumbersSection.x = 64; lateralNumbersSection.y = 0;
			lateralNumbersSection.w = 16; lateralNumbersSection.h = 16;

			if (numberBlink < 2)
			{
				App->render->Blit(lateralNumbersBlink, 4, 176, &lateralNumbersSection);
			}
			else
			{
				App->render->Blit(lateralNumbersTexture, 4, 176, &lateralNumbersSection);
			}
		}

		numberBlink++;
		if (numberBlink > 4) {
			numberBlink = 0;
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

		if (App->playground->gameOver == false)
		{
			if (levelLines <= 0 && App->playground->lineLimit == false && App->game->statePlay1 == true) {
				//WIN
				App->game->stateWin = true;
				App->game->statePlay1 = false;
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
			App->game->stateLose = true;
			App->game->statePlay1 = false;
		}
	}

	if (App->game->stateLose == true) {
		//Game Over

		if (playMusic) {
			App->audio->PlayMusic("", 1.0f);
			playMusic = false;
		}

		//CURTAIN ANIMATION CLOSING  NOO VA :( (ahora si :))
		App->render->Blit(curtainTexture, 128, 96, &(curtainClosing.GetCurrentFrame()));

		//Draw dead blocks (player 1)
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

		App->render->Blit(goTexture, 32, 0, NULL);

		if (loseDelay <= 0) {
			App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		}
		loseDelay--;
	}

	if (App->game->stateWin == true) {
		//WIN

		if (playMusic) {
			App->audio->PlayMusic("", 1.0f);
			App->audio->PlayFx(App->audio->roundCompletedAndBonusPointBars);
			playMusic = false;
		}

		//Draw dead blocks (player 1)
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

		if (winDelay <= 0) {
			//CURTAIN ANIMATION CLOSING  NOO VA :( (si que va :))
			App->render->Blit(curtainTexture, 128, 96, &(curtainClosing.GetCurrentFrame()));
		}

		if (winDelay<=-60) {
			if (currentLevel < 11) { ResetLevel(); }
			else{ App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90); }
		}
		else{ winDelay--; }
	}

	if (App->game->multiplayer && (App->game->statePlay1 || App->game->stateLine1 || App->game->statePlay2 || App->game->stateLine2))
	{

		if (!playMusic) {
			App->audio->PlayMusic("Assets/audio/MultiplayerOST.ogg", 1.0f);
			playMusic = true;
		}

		//Lateral bars for player 1
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

		//lateral bars for player 2
		if (App->playground2->lines == 4)
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
				App->playground2->lines = 0;
			}

			App->render->Blit(lateralBars, 220, 65 + lateralBarsY, &(lateralBarsAnim.GetCurrentFrame()));
			App->render->Blit(lateralBars, 308, 65 + lateralBarsY, &(lateralBarsAnim.GetCurrentFrame()));
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

		//Draw dead blocks (player 2)
		for (size_t i = 0; i < 23; i++)
		{
			for (size_t j = 0; j < 12; j++)
			{
				if (playground2[i][j] != 0 && playground2[i][j] != 255)
					App->tiles->BlitText2(j, i, Dead_Tetromino, playground2[i][j], App->playground2->block, false);
			}
		}

		if (App->playground->gameOver == false)
		{
			//Draw alive block (player 1)
			if (App->playground->block.id != 255)
				App->tiles->BlitText(App->playground->block.x, App->playground->block.y, Alive_Tetromino, NULL, App->playground->block, true);
		}
		else
		{
			//Game over player 1
			App->render->Blit(goTexture, 32, 0, NULL);
			App->game->statePlay1 = false;
			if (App->playground2->gameOver) { App->game->stateEndMultiplayer = true; }
		}

		if (App->playground2->gameOver == false)
		{
			//Draw alive block (player 2)
			if (App->playground2->block.id != 255)
				App->tiles->BlitText2(App->playground2->block.x, App->playground2->block.y, Alive_Tetromino, NULL, App->playground2->block, true);
		}
		else
		{
			App->render->Blit(goTexture, 240, 0, NULL);
			//Game over player 2
			App->game->statePlay2 = false;
			if (App->playground->gameOver) { App->game->stateEndMultiplayer = true; }
		}
	}

	if (App->game->stateEndMultiplayer)
	{
		//Game Over

		if (playMusic) {
			App->audio->PlayMusic("", 1.0f);
			playMusic = false;
		}

		//CURTAIN ANIMATION CLOSING  NOO VA :( (ahora si :))
		App->render->Blit(curtainTexture, 128, 96, &(curtainClosing.GetCurrentFrame()));

		//Draw dead blocks (player 1)
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

		//Draw dead blocks (player 2)
		for (size_t i = 0; i < 23; i++)
		{
			for (size_t j = 0; j < 12; j++)
			{
				if (playground2[i][j] != 0 && playground2[i][j] != 255)
					App->tiles->BlitText2(j, i, Dead_Tetromino, playground2[i][j], App->playground2->block, false);
			}
		}

		App->render->Blit(goTexture, 32, 0, NULL);
		App->render->Blit(goTexture, 240, 0, NULL);

		if (loseDelay <= 0) {
			App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		}
		loseDelay--;
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneGame::CleanUp()
{
	App->game->Disable();
	App->playground->Disable();
	if (App->game->multiplayer){ App->playground2->Disable(); }

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