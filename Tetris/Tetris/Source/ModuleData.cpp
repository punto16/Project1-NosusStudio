#include "Application.h"

#include "ModuleData.h"

ModuleData::ModuleData(bool isEnabled) : Module(isEnabled)
{

}

ModuleData::~ModuleData()
{

}

bool ModuleData::Start() {
	bool ret = true;

	return ret;
}