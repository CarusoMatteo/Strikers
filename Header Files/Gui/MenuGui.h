#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>

#include "IGui.h"

using glm::fvec3;

class MenuGui : public IGui
{
public:
	MenuGui(fvec3 *clearColorRef);

	void drawGui() override;
	fvec3 *getClearColorRef() override
	{
		return this->clearColorRef;
	}

private:
	fvec3 *clearColorRef;
};
