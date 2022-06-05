#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 16
#define NUM_LEVELS 1

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleController;

class ModuleTextures;
class ModuleAudio;

class ModuleData;
class ModulePlayGround;
class ModulePlayGround2;

class SceneIntro;
class SceneMenu;
class SceneGame;
class ModuleGame;

class ModuleFadeToBlack;
class ModuleFonts;
class ModuleTiles;
class ModuleRender;


class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleController* controller  = nullptr;

	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModuleData* data = nullptr;
	ModulePlayGround* playground = nullptr;
	ModulePlayGround2* playground2 = nullptr;

	SceneIntro* sceneIntro = nullptr;
	SceneMenu* sceneMenu = nullptr;
	SceneGame* sceneGame = nullptr;
	ModuleGame* game = nullptr;

	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;
	ModuleTiles* tiles = nullptr;
	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__