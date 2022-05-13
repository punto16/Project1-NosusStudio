#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/sprite_title.png");
	introTexture = App->textures->Load("Assets/Sprites/PreTitle.png");
	App->audio->PlayMusic("", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	if ((!play_intro) && (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN))
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	else if ((!play_intro)&&(App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN))
	{
		return Update_Status::UPDATE_STOP;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	uint tex_w, tex_h;
	App->textures->GetTextureSize(introTexture, tex_w, tex_h);
	int camera = ((App->render->camera.y / SCREEN_SIZE) + SCREEN_HEIGHT);

	if (camera == tex_h) {
		play_intro = false;
	}

	if (play_intro) {
		App->render->Blit(introTexture, 0, 0, NULL);
		App->render->camera.y ++;
	}
	else {
		App->render->camera.y = 0;
		App->render->Blit(bgTexture, 0, 0, NULL);
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	LOG("Deleting background assets");

	App->textures->Unload(bgTexture);

	return true;
}