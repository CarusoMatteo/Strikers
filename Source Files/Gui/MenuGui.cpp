#include "../../Header Files/Gui/MenuGui.h"

MenuGui::MenuGui(fvec3 *clearColorRef) : IGui(), clearColorRef(clearColorRef)
{
}

MenuGui::~MenuGui()
{
	ImGui_ImplOpenGL3_Shutdown(); // Rilascia risorse renderer OpenGL3
	ImGui_ImplGlfw_Shutdown();	  // Rilascia risorse integrazione GLFW
	ImGui::DestroyContext();	  // Distrugge contesto ImGui liberando memoria
}

void MenuGui::drawGui()
{
	// Prepares a new frame for ImGui
	ImGui_ImplGlfw_NewFrame();
	// Prepares a new frame for OpenGL3 rendering
	ImGui_ImplOpenGL3_NewFrame();
	// Starts a new recording for a ImGui frame
	ImGui::NewFrame();
	// Disables the ini file saving/loading.
	ImGui::GetIO().IniFilename = nullptr;

	settingsWindow(10, 10);

	// Ends the ImGui frame declaration.
	ImGui::End();
	// Renders the ImGui frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MenuGui::settingsWindow(float xpos, float ypos)
{
	dvec2 *mousePosition = InputEvents::getCursorPosition();

	// Sets the position for the next window.
	ImGui::SetNextWindowPos(ImVec2(xpos, ypos));

	ImGui::Begin("Impostazioni", NULL,
				 ImGuiWindowFlags_NoResize |
					 ImGuiWindowFlags_AlwaysAutoResize |
					 ImGuiWindowFlags_NoMove);

	// Editable background color.
	ImGui::ColorEdit3("Colore di Sfondo", (float *)this->clearColorRef);
	// Shows mouse coordinates.
	ImGui::Text("Coordinate Mouse relative alla finestra GLFW: (%.1f, %.1f)", mousePosition->x, mousePosition->y);
	// Checkbox to toggle wireframe mode.
	ImGui::Checkbox("Wireframe", MeshBB::getIsWireframeRef());
	ImGui::Checkbox("Bounding Box", MeshBB::shouldDrawBoundingBoxRef());
}