#ifndef __MODULE_TILES_H__
#define __MODULE_TILES_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_TETROMINOS 10
#define MAX_TETROMINO_BLOCKS 256

struct SDL_Texture;

struct Tetrominos
{
	// Lookup table. All characters displayed in the same order as the texture
	uchar table[MAX_TETROMINO_BLOCKS];

	// The font texture
	SDL_Texture* texture = nullptr;

	// Font setup data
	uint totalLength;
	uint rows, columns;
	uint char_w, char_h;
};

class ModuleTiles : public Module
{
public:

	// Constructor
	ModuleTiles(bool isEnabled);

	// Destructor
	~ModuleTiles();

	// Loads a font file from a texture
	// Returns a font index from the fonts array
	// Param texturePath	- The path to the texture file
	// Param characters		- The lookup table. All characters displayed in the same order as the texture
	// Param rows			- The amount of character rows in the texture
	int Load(const char* texturePath, const uchar* characters, uint rows = 1);

	// Removes a font by its index
	// Unloads the texture and removes it from the fonts array
	void UnLoad(int fontIndex);

	// Create a surface from text
	void BlitText(int x, int y, int fontIndex, const uchar* text) const;

private:
	// An array to keep track and store all loaded fonts
	Tetrominos tetrominos[MAX_TETROMINOS];
};


#endif // __ModuleTiles_H__