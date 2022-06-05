#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTiles.h"
#include "SceneGame.h"
#include "ModulePlayGround.h"
#include "ModulePlayGround2.h"

#include<string.h>

ModuleTiles::ModuleTiles(bool isEnabled) : Module(isEnabled)
{

}

ModuleTiles::~ModuleTiles()
{

}

// Load new texture from file path
int ModuleTiles::Load(const char* texture_path, uint columns, uint rows)
{
	int len = columns * rows;
	int id = -1;

	if (texture_path == nullptr || columns==NULL || rows == NULL)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || len >= MAX_TETROMINO_BLOCKS)
	{
		LOG("Could not load font at %s with '%d' columns", texture_path, columns);
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
	tetromino.columns = columns;
	tetromino.totalLength = len;

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

	if (block)
	{
		blockText = actual_block.rotation;

		switch (actual_block.id)
		{
		case 0:	break;
		case 1:	blockText += 4;	 break;
		case 2:	blockText += 8;	 break;
		case 3:	blockText += 12; break;
		case 4:	blockText += 16; break;
		case 5:	blockText += 20; break;
		case 6:	blockText += 24; break;
		default: break;
		}

		//we divide by 4 because is the width and height of the block matrix
		if (actual_block.on_playground == true) {
			x = (x * (tetromino->block_w / 4)) + App->sceneGame->x_TileMap;
			y = (y * (tetromino->block_h / 4)) + App->sceneGame->y_TileMap;
		}
	}
	else if (tile != NULL) {
		blockText = ((int)tile) - 1;
		x = (x * tetromino->block_w) + App->sceneGame->x_TileMap;
		y = (y * tetromino->block_h) + App->sceneGame->y_TileMap;
	}
	else {
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	SDL_Rect spriteRect;
	spriteRect.w = tetromino->block_w;
	spriteRect.h = tetromino->block_h;

	// Retrieve the position of the current character in the sprite
	spriteRect.x = spriteRect.w * (blockText % tetromino->columns);
	spriteRect.y = spriteRect.h * (blockText / tetromino->columns);

	App->render->Blit(tetromino->texture, x, y, &spriteRect, 0.0f, false);

	// Advance the position where we blit the next character
	x += spriteRect.w;
}

void ModuleTiles::BlitText2(int x, int y, int font_id, uint tile, Block2 actual_block, bool block)
{
	if (font_id < 0 || font_id >= MAX_TETROMINOS || tetrominos[font_id].texture == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const Tetrominos* tetromino = &tetrominos[font_id];

	if (block)
	{
		blockText = actual_block.rotation;

		switch (actual_block.id)
		{
		case 0:	break;
		case 1:	blockText += 4;	 break;
		case 2:	blockText += 8;	 break;
		case 3:	blockText += 12; break;
		case 4:	blockText += 16; break;
		case 5:	blockText += 20; break;
		case 6:	blockText += 24; break;
		default: break;
		}

		//we divide by 4 because is the width and height of the block matrix
		if (actual_block.on_playground == true) {
			x = (x * (tetromino->block_w / 4)) + App->sceneGame->x_TileMap2;
			y = (y * (tetromino->block_h / 4)) + App->sceneGame->y_TileMap;
		}
	}
	else if (tile != NULL) {
		blockText = ((int)tile) - 1;
		x = (x * tetromino->block_w) + App->sceneGame->x_TileMap2;
		y = (y * tetromino->block_h) + App->sceneGame->y_TileMap;
	}
	else {
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	SDL_Rect spriteRect;
	spriteRect.w = tetromino->block_w;
	spriteRect.h = tetromino->block_h;

	// Retrieve the position of the current character in the sprite
	spriteRect.x = spriteRect.w * (blockText % tetromino->columns);
	spriteRect.y = spriteRect.h * (blockText / tetromino->columns);

	App->render->Blit(tetromino->texture, x, y, &spriteRect, 0.0f, false);

	// Advance the position where we blit the next character
	x += spriteRect.w;
}