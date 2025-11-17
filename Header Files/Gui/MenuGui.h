#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>

#include "IGui.h"

using glm::fvec3;

/**
 * @brief Represents the main menu GUI of the application.
 */
class MenuGui : public IGui
{
public:
	MenuGui(fvec3 *clearColorRef, bool *changeSceneRef, float bestScore);

	void drawGui() override;
	fvec3 *getClearColorRef() override
	{
		return this->clearColorRef;
	}

private:
	fvec3 *clearColorRef;
	bool *startGameRef;
	float bestScore;

	void difficultyWindow(float xpos, float ypos);
};
