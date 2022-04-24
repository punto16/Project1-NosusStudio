#include "ModulePlayGround.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"

#include <stdio.h>

ModulePlayGround::ModulePlayGround(bool startEnabled)
{
}

ModulePlayGround::~ModulePlayGround()
{
}

Update_Status ModulePlayGround::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayGround::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayGround::PostUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}
