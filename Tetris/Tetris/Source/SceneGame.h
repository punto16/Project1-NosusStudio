#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneGame : public Module
{
public:
	//Constructor
	SceneGame(bool startEnabled);

	//Destructor
	~SceneGame();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:
	
	int levelLines = 5;

	bool playMusic = false;

	int winDelay = 120;


	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* lateralNumbersTexture = nullptr;
	SDL_Texture* goTexture = nullptr;

	SDL_Texture* curtainTexture = nullptr;
	SDL_Texture* lateralBars = nullptr;

	SDL_Rect lateralNumbersSection;

	SDL_Texture* Russian1 = nullptr;
	SDL_Texture* Russian2 = nullptr;
	SDL_Texture* Russian3 = nullptr;



	Animation lateralBarsAnim;
	unsigned int lateralBarCounter;
	int lateralBarsY = 0;

	//animations
	Animation curtainOpening;
	Animation curtainClosing;
	Animation Dance1;
	Animation Dance2;
	Animation Dance3;


	int Dead_Tetromino = -1;
	int Alive_Tetromino = -1;

	uint playground[23][12] =
	{
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,255,255,255,255,255,255,255,255,255,255,255,
	};
	int x_TileMap = 24;
	int y_TileMap = 24;

	uint playground2[23][12] =
	{
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,0,0,0,0,0,0,0,0,0,0,255,
		255,255,255,255,255,255,255,255,255,255,255,255,
	};
	int x_TileMap2 = 216;
};

#endif