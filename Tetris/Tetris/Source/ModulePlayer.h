#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;


public:

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Fonts
	int Tetris_font_black = -1;

	//UI elements
	uint score = 000;
	char scoreText[10] = { "\0" };

	uint lines = 000;
	char linesText[10] = { "\0" };

	uint level = 001;
	char levelText[10] = { "\0" };

};

#endif //!__MODULE_PLAYER_H__