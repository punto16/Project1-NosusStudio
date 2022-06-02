#ifndef __MODULE_TILES_H__
#define __MODULE_TILES_H__

#include "Module.h"
#include "ModulePlayGround.h"
#include "ModulePlayGround2.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_TETROMINOS 10
#define MAX_TETROMINO_BLOCKS 256

struct SDL_Texture;

struct Tetrominos
{
	// Lookup table. All characters displayed in the same order as the texture
	char table[MAX_TETROMINO_BLOCKS];
	char dictionary[MAX_TETROMINO_BLOCKS];

	// The font texture
	SDL_Texture* texture = nullptr;

	// Font setup data
	uint totalLength;
	uint rows, columns;
	uint block_w, block_h;
};

class ModuleTiles : public Module
{
public:

	uint blockText;
	char blockText_text[10] = { "\0" };

	// Constructor
	ModuleTiles(bool isEnabled);

	// Destructor
	~ModuleTiles();

	// Loads a font file from a texture
	// Returns a font index from the fonts array
	// Param texturePath	- The path to the texture file
	// Param characters		- The lookup table. All characters displayed in the same order as the texture
	// Param rows			- The amount of character rows in the texture
	int Load(const char* texturePath, const char* tiles, uint rows = 1);

	// Removes a font by its index
	// Unloads the texture and removes it from the fonts array
	void UnLoad(int fontIndex);

	// Create a surface from text
	void BlitText(int x, int y, int fontIndex, uint text, Block actual_block, bool block = false);
	void BlitText2(int x, int y, int fontIndex, uint text, Block2 actual_block, bool block = false);

private:
	// An array to keep track and store all loaded fonts
	Tetrominos tetrominos[MAX_TETROMINOS];
};


#endif // __ModuleTiles_H__