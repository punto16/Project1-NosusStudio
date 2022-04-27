#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTiles.h"

#include<string.h>

ModuleTiles::ModuleTiles(bool isEnabled) : Module(isEnabled)
{

}

ModuleTiles::~ModuleTiles()
{

}

// Load new texture from file path
int ModuleTiles::Load(const char* texture_path, const uchar* tiles, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || tiles == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || strlen(reinterpret_cast<const char*>(tiles)) >= MAX_TETROMINO_BLOCKS)
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

	for (size_t i = 0; i < strlen(reinterpret_cast<const char*>(tiles)); i++)
	{
		tetromino.table[i] = tiles[i];
	}
	tetromino.totalLength = strlen(reinterpret_cast<const char*>(tiles));
	tetromino.columns = tetrominos[id].totalLength / rows;

	uint tex_w, tex_h;
	App->textures->GetTextureSize(tex, tex_w, tex_h);
	tetromino.char_w = tex_w / tetromino.columns;
	tetromino.char_h = tex_h / tetromino.rows;

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

void ModuleTiles::BlitText(int x, int y, int font_id, const uchar* tex) const
{
	if (tex == nullptr || font_id < 0 || font_id >= MAX_TETROMINOS || tetrominos[font_id].texture == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const Tetrominos* tetromino = &tetrominos[font_id];
	SDL_Rect spriteRect;
	uint len = strlen(reinterpret_cast<const char*>(tex));

	spriteRect.w = tetromino->char_w;
	spriteRect.h = tetromino->char_h;

	for (uint i = 0; i < len; ++i)
	{
		uint charIndex = 0;

		// Find the location of the current character in the lookup table
		for (uint j = 0; j < tetromino->totalLength; ++j)
		{
			if (tetromino->table[j] == tex[i])
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
