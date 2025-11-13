#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>

#include "IGui.h"

using glm::fvec3;

class GameGui : public IGui
{
public:
	GameGui(fvec3 *clearColorRef, float *scoreRef);
	void drawGui() override;
	fvec3 *getClearColorRef() override
	{
		return this->clearColorRef;
	}

private:
	void settingsWindow(float xpos, float ypos);
	void gameInfoWindow(float xpos, float ypos);

	fvec3 *clearColorRef;
	float *scoreRef;
};
