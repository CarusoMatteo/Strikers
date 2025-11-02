#pragma once
#include "IGui.h"

#include <ImGui\imgui.h>
#include <ImGui\imgui_impl_glfw.h>
#include <ImGui\imgui_impl_opengl3.h>

#include "../MeshBB.h"
#include "../InputEvents.h"

class MenuGui : public IGui
{
public:
	MenuGui(vec3 *clearColorRef);
	~MenuGui();
	void drawGui() override;

private:
	void settingsWindow(float xpos, float ypos);

	vec3 *clearColorRef;
};
