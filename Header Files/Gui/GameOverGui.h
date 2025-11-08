#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "IGui.h"

class GameOverGui : public IGui
{
public:
	GameOverGui(fvec3 *clearColorRef);
	void drawGui() override;
	fvec3 *getClearColorRef() override
	{
		return this->clearColorRef;
	}

private:
	void gameOverWindow(float xpos, float ypos);

	fvec3 *clearColorRef;
};
