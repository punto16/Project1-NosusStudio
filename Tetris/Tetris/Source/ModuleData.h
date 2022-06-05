#ifndef __MODULE_DATA_H__
#define __MODULE_DATA_H__

#include "Module.h"

class ModuleData : public Module
{
public:
	// Constructor
	ModuleData(bool startEnabled);

	// Destructor
	~ModuleData();

	// Called when the module is activated
	// Loads the necessary textures for the 

	bool Start() override;


public:

	uint high_score = 0;
	uint high_score_multiplayer = 0;

};

#endif //!__MODULE_DATA_H__