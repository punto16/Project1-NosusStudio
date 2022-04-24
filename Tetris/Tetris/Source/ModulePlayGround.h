#ifndef __MODULE_PLAYGROUND_H__
#define __MODULE_PLAYGROUND_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModulePlayGround : public Module
{
public:
	// Constructor
	ModulePlayGround(bool startEnabled);

	// Destructor
	~ModulePlayGround();

	// Reads the matrix of the playgraund depending on the current level
	Update_Status PreUpdate() override;

	// Moves the piece
	Update_Status Update() override;

	// Modifies the matrix depending on the current level
	Update_Status PostUpdate() override;


public:



};

#endif //!__MODULE_PLAYGROUND_H__