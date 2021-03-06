#ifndef __MODULE_GAME_H__
#define __MODULE_GAME_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleGame : public Module
{
public:
	// Constructor
	ModuleGame(bool startEnabled);

	// Destructor
	~ModuleGame();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	bool ModuleGame::CleanUp() override;


public:

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	bool stateStartLevel = true;
	bool stateWin = false;
	bool stateTePasasteElJuegoPerro = false;
	bool stateLose = false;
	bool stateEndGame = false;

	bool stateLine1 = false;
	bool stateLine2 = false;
	bool statePlay1 = false;
	bool statePlay2 = false;

	bool multiplayer = false;
	bool stateEndMultiplayer = false;

	// Fonts
	int Tetris_font_black		= -1;
	int Tetris_font_blue		= -1;
	int Tetris_font_brown		= -1;
	int Tetris_font_darkblue	= -1;
	int	Tetris_font_lightblue	= -1;
	int	Tetris_font_purpura		= -1;
	int	Tetris_font_red			= -1;
	int	Tetris_font_white		= -1;

	int fontMiddle				= -1;
	int fontScore				= -1;
	int fontRight				= -1;


	//textures
	
	SDL_Texture* rainbowBar = nullptr;
	SDL_Rect rainbowBarSection = { 0,16,8,2 };
	
	//UI elements
	uint scorePlayer1;
	char scoreTextPlayer1[10] = { "\0" };

	uint totalLines;
	char linesText[10] = { "\0" };

	uint scorePlayer2;
	char scoreTextPlayer2[10] = { "\0" };

	uint totalLinesPlayer2;
	char linesTextPlayer2[10] = { "\0" };

	uint round;
	char roundText[10] = { "\0" };

	uint credits = 0;
	char creditsText[10] = { "\0" };

	char high_scoreText[10] = { "\0" };

	uint rainbow = 1;

	char linesLeftText[10] = { "\0" };

	int timer = 0;
	int delayStart = 40;
};

#endif //!__MODULE_GAME_H__