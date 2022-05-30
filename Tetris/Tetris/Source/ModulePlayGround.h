#ifndef __MODULE_PLAYGROUND_H__
#define __MODULE_PLAYGROUND_H__

#include <time.h>
#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

struct Block
{
    int id = 255;
    int rotation = 0;
    uint tiles[4][4];
    int x, y;
    int inputX = 0, inputY = 1;
    bool on_playground = false;
};

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

    void SaveInput();

    void NextBlock();

    int RandomBlock();

    void LoadBlockMatrix(Block& block);

    bool IsColliding(int x2, int y2, Block& block);

    void MoveBlock(int x2, int y2);

    void RotateBlock();

    void DeathSequence();

    void CheckLine();

    void StateLine();

    bool GameoverCheck();

    void Score();

public:
	int currentModule;
    int lines;
    int height;

    int fCountL = 0;
    int fCountY = 0;
    int fCountX = 0;

    Block block, nextBlock, blockCheck;

    bool isAlive = true;
    bool rotate = false;
    bool gameOver = false;

    int linePositionIndex = 0;
    int linePositionList[4] = { -1, -1, -1, -1 };
    int lineColorIndex = 0;
    int lineColorList[6] = { 136, 137, 138, 139, 140, 141 };

    uint blockList[7][4][4][4] = //color, rotation, x, y
    {
        //red
        {
            {
                { 1, 2, 2, 3 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 4, 0, 0 },
                { 0, 5, 0, 0 },
                { 0, 5, 0, 0 },
                { 0, 6, 0, 0 }
            },
            {
                { 1, 2, 2, 3 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 4, 0, 0 },
                { 0, 5, 0, 0 },
                { 0, 5, 0, 0 },
                { 0, 6, 0, 0 }
            },
        },
        //yellow
        {
            {
                { 46, 47, 59, 0 },
                { 0, 0, 51, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
           {
                { 56, 48, 0, 0 },
                { 50, 0, 0, 0 },
                { 51, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 49, 0, 0, 0 },
                { 58, 47, 48, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 49, 0, 0 },
                { 0, 50, 0, 0 },
                { 46, 57, 0, 0 },
                { 0, 0, 0, 0 }
            },
        },
        //violet
        {
            {
                { 71, 62, 63, 0 },
                { 66, 0, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 64, 0, 0, 0 },
                { 65, 0, 0, 0 },
                { 73, 63, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 0, 64, 0 },
                { 61, 62, 72, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 61, 74, 0, 0 },
                { 0, 65, 0, 0 },
                { 0, 66, 0, 0 },
                { 0, 0, 0, 0 }
            },
        },
        //green
        {
            {
                { 16, 24, 18, 0 },
                { 0, 21, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 19, 0, 0, 0 },
                { 23, 18, 0, 0 },
                { 21, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 19, 0, 0 },
                { 16, 22, 18, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 19, 0, 0 },
                { 16, 25, 0, 0 },
                { 0, 21, 0, 0 },
                { 0, 0, 0, 0 }
            },
        },
        //cian
        {
            {
                { 0, 86, 78, 0 },
                { 76, 87, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 79, 0, 0, 0 },
                { 88, 89, 0, 0 },
                { 0, 81, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 86, 78, 0 },
                { 76, 87, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 79, 0, 0, 0 },
                { 88, 89, 0, 0 },
                { 0, 81, 0, 0 },
                { 0, 0, 0, 0 }
            },
        },
        //orange
        {
            {
                { 91, 104, 0, 0 },
                { 0, 103, 93, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 94, 0, 0 },
                { 101, 102, 0, 0 },
                { 96, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 91, 104, 0, 0 },
                { 0, 103, 93, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 0, 94, 0, 0 },
                { 101, 102, 0, 0 },
                { 96, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
        },
        //blue
        {
            {
                { 41, 44, 0, 0 },
                { 43, 42, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 41, 44, 0, 0 },
                { 43, 42, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 41, 44, 0, 0 },
                { 43, 42, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            },
            {
                { 41, 44, 0, 0 },
                { 43, 42, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 }
            }
        }
    };
};

#endif //!__MODULE_PLAYGROUND_H__