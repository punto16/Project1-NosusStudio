#pragma once
#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneMenu : public Module
{
public:
	//Constructor
	SceneMenu(bool startEnabled);

	//Destructor
	~SceneMenu();

	// Called when the module is activated
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	bool SceneMenu::CleanUp() override;

	void selectionToRight();
	void selectionToLeft();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* modebgTexture = nullptr;
	SDL_Texture* diffbgTexture = nullptr;
	SDL_Texture* leftArrow = nullptr;
	SDL_Texture* rightArrow = nullptr;

	bool play_diff = false;
	int selection;
	
};

#endif