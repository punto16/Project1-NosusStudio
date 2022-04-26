#ifndef __MODULE_PLAYGROUND_H__
#define __MODULE_PLAYGROUND_H__

#include <time.h>
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

	bool Start() override;

	// Reads the matrix of the playgraund depending on the current level
	Update_Status PreUpdate() override;

	// Moves the piece
	Update_Status Update() override;

	// Modifies the matrix depending on the current level
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();


    int NextPiece()
    {
        return rand() % 7;
    }



public:

	int currentModule;

	char map[10][22];

	struct block
	{
		int id;
		int tiles[4][4];
		int x, y;
	};

    int red[2][4][4] =
    {
        {
            { 1, 1, 1, 1 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 }
        },
    };


    int yellow[4][4][4] =
    {
        {
            { 1, 1, 1, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 },
            { 1, 1, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 1, 0, 0, 0 },
            { 1, 1, 1, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 1, 1, 0, 0 },
            { 1, 0, 0, 0 },
            { 1, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
    };


    int violet[4][4][4] =
    {
        {
            { 1, 1, 1, 0 },
            { 1, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 1, 1, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 0, 1, 0 },
            { 1, 1, 1, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 1, 0, 0, 0 },
            { 1, 0, 0, 0 },
            { 1, 1, 0, 0 },
            { 0, 0, 0, 0 }
        },
    };

    
    int green[4][4][4] =
    {
        {
            { 1, 1, 1, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 1, 0, 0 },
            { 1, 1, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 1, 0, 0 },
            { 1, 1, 1, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 1, 0, 0, 0 },
            { 1, 1, 0, 0 },
            { 1, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
    };

    int cian[2][4][4] =
    {
        {
            { 0, 1, 1, 0 },
            { 1, 1, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 1, 0, 0, 0 },
            { 1, 1, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 0, 0 }
        },
    };


    int orange[2][4][4] =
    {
        {
            { 1, 1, 0, 0 },
            { 0, 1, 1, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 1, 0, 0 },
            { 1, 1, 0, 0 },
            { 1, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
    };

    int blue[4][4] =
    {
            { 1, 1, 0, 0 },
            { 1, 1, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
    };


};

#endif //!__MODULE_PLAYGROUND_H__