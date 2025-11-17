#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "IGui.h"

/**
 * @brief The Gui that's shown when the player runs out of health.
 */
class GameOverGui : public IGui
{
public:
	GameOverGui(fvec3 *clearColorRef, bool *startGame);
	void drawGui() override;
	fvec3 *getClearColorRef() override
	{
		return this->clearColorRef;
	}

private:
	void gameOverWindow(float xpos, float ypos);

	fvec3 *clearColorRef;
	bool *startGame;
};
