#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTiles.h"
#include "SceneLevel1.h"
#include "ModulePlayGround.h"

#include<string.h>

ModuleTiles::ModuleTiles(bool isEnabled) : Module(isEnabled)
{

}

ModuleTiles::~ModuleTiles()
{

}

// Load new texture from file path
int ModuleTiles::Load(const char* texture_path, const char* tiles, uint rows)
{
	int len = strlen(tiles);
	int id = -1;

	if (texture_path == nullptr || tiles == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || len >= MAX_TETROMINO_BLOCKS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, tiles);
		return id;
	}

	id = 0;
	for (; id < MAX_TETROMINOS; ++id)
		if (tetrominos[id].texture == nullptr)
			break;

	if (id == MAX_TETROMINOS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_TETROMINOS);
		return id;
	}

	Tetrominos& tetromino = tetrominos[id];

	tetromino.texture = tex;
	tetromino.rows = rows;

	for (size_t i = 0; i < len; i++)
	{
		tetromino.table[i] = tiles[i];
	}
	int count = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (tiles[i]!=' ') {
			tetromino.dictionary[count] = tiles[i];
			count++;
		}
	}
	tetromino.totalLength = len;
	tetromino.columns = tetrominos[id].totalLength / rows;

	uint tex_w, tex_h;
	App->textures->GetTextureSize(tex, tex_w, tex_h);
	tetromino.block_w = tex_w / tetromino.columns;
	tetromino.block_h = tex_h / tetromino.rows;

	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void ModuleTiles::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_TETROMINOS && tetrominos[font_id].texture != nullptr)
	{
		App->textures->Unload(tetrominos[font_id].texture);
		tetrominos[font_id].texture = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

void ModuleTiles::BlitText(int x, int y, int font_id, uint tile, Block actual_block, bool block)
{
	if (font_id < 0 || font_id >= MAX_TETROMINOS || tetrominos[font_id].texture == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const Tetrominos* tetromino = &tetrominos[font_id];

	if (block) {
		blockText = actual_block.rotation;

		switch (actual_block.id)
		{
		case 0:
			break;
		case 1:
			blockText += 4;
			break;
		case 2:
			blockText += 8;
			break;
		case 3:
			blockText += 12;
			break;
		case 4:
			blockText += 16;
			break;
		case 5:
			blockText += 20;
			break;
		case 6:
			blockText += 24;
			break;
		default:
			break;
		}

		blockText_text[0] = tetromino->table[blockText];

		//we divide by 4 because is the width and height of the block matrix
		if (actual_block.on_playground == true) {
			x = (x * (tetromino->block_w / 4)) + App->sceneLevel_1->x_TileMap;
			y = (y * (tetromino->block_h / 4)) + App->sceneLevel_1->y_TileMap;
		}
	}
	else if (tile != NULL) {
		blockText_text[0] = tetromino->table[((int)tile) - 1];
		x = (x * tetromino->block_w) + App->sceneLevel_1->x_TileMap;
		y = (y * tetromino->block_h) + App->sceneLevel_1->y_TileMap;
	}
	else {
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	SDL_Rect spriteRect;
	uint len = 1;

	spriteRect.w = tetromino->block_w;
	spriteRect.h = tetromino->block_h;

	for (uint i = 0; i < len; ++i)
	{
		uint charIndex = 0;

		// Find the location of the current character in the lookup table
		for (uint j = 0; j < tetromino->totalLength; ++j)
		{
			if (tetromino->table[j] == blockText_text[i])
			{
				charIndex = j;
				break;
			}
		}

		// Retrieve the position of the current character in the sprite
		spriteRect.x = spriteRect.w * (charIndex % tetromino->columns);
		spriteRect.y = spriteRect.h * (charIndex / tetromino->columns);

		App->render->Blit(tetromino->texture, x, y, &spriteRect, 0.0f, false);

		// Advance the position where we blit the next character
		x += spriteRect.w;
	}
}
