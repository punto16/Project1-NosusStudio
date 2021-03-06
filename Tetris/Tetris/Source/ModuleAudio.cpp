#include "ModuleAudio.h"

#include "Application.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_FX; ++i)
		soundFx[i] = nullptr;
}

ModuleAudio::~ModuleAudio()
{

}

bool ModuleAudio::Init()
{
	LOG("Loading Audio Mixer");
	bool ret = true;

	//Initialize audio subsystem
	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//Load support for OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	//Initialize SDL_mixer
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}

	newLevelFx = App->audio->LoadFx("Assets/audio/new_level.wav");
	blockAppearFx = App->audio->LoadFx("Assets/audio/block_appear.wav");
	bonusPointBarsFx = App->audio->LoadFx("Assets/audio/bonus_point_bars.wav");
	gameOverFx = App->audio->LoadFx("Assets/audio/game_over.wav");
	greatScoreFx = App->audio->LoadFx("Assets/audio/great_score.wav");
	hitFx = App->audio->LoadFx("Assets/audio/hit.wav");
	insertCoinFx = App->audio->LoadFx("Assets/audio/insert_coin.wav");
	lineFx = App->audio->LoadFx("Assets/audio/line.wav");
	roundCompletedFx = App->audio->LoadFx("Assets/audio/round_completed.wav");
	selectDiffFx = App->audio->LoadFx("Assets/audio/select_diff.wav");
	changeDiffFx = App->audio->LoadFx("Assets/audio/change_diff.wav");
	roundCompletedAndBonusPointBars = App->audio->LoadFx("Assets/audio/round_ended_bars.wav");
	rusoMusic1 = App->audio->LoadFx("Assets/audio/Ruso1.wav");
	rusoMusic2 = App->audio->LoadFx("Assets/audio/Ruso2.wav");
	rusoMusic3 = App->audio->LoadFx("Assets/audio/Ruso3.wav");

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if(music != NULL)
	{
		Mix_FreeMusic(music);
	}

	for (uint i = 0; i < MAX_FX; ++i)
	{
		if(soundFx[i] != nullptr)
			Mix_FreeChunk(soundFx[i]);
	}
	
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;

	if(music != NULL)
	{
		if(fade_time > 0.0f)
		{
			// Warning: This call blocks the execution until fade out is done
			Mix_FadeOutMusic((int) (fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if(music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if(fade_time > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

uint ModuleAudio::LoadFx(const char* path)
{
	uint ret = 0;
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if(chunk == nullptr)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		for (ret = 0; ret < MAX_FX; ++ret)
		{
			if (soundFx[ret] == nullptr)
			{
				soundFx[ret] = chunk;
				break;
			}
		}
	}

	return ret;
}


bool ModuleAudio::PlayFx(uint index, int repeat)
{
	bool ret = false;
	
	if(soundFx[index] != nullptr)
	{
		Mix_PlayChannel(-1, soundFx[index], repeat);
		ret = true;
	}

	return ret;
}