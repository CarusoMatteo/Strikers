#include "../../Header Files/Gui/GameOverGui.h"

#include "../../Header Files/Mesh.h"
#include "../../Header Files/MeshBB.h"
#include "../../Header Files/InputEvents.h"

GameOverGui::GameOverGui(fvec3 *clearColorRef) : IGui(), clearColorRef(clearColorRef)
{
}

void GameOverGui::drawGui()
{
	// Prepares a new frame for ImGui
	ImGui_ImplGlfw_NewFrame();
	// Prepares a new frame for OpenGL3 rendering
	ImGui_ImplOpenGL3_NewFrame();
	// Starts a new recording for a ImGui frame
	ImGui::NewFrame();
	// Disables the ini file saving/loading.
	ImGui::GetIO().IniFilename = nullptr;

	gameOverWindow(InputEvents::getCurrentWindowSize().x * 0.5f, InputEvents::getCurrentWindowSize().y * 0.5f);

	// Ends the ImGui frame declaration.
	ImGui::End();
	// Renders the ImGui frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GameOverGui::gameOverWindow(float xpos, float ypos)
{
	// Sets the position for the next window.
	ImGui::SetNextWindowPos(ImVec2(xpos, ypos));

	ImGui::Begin("Game Over", NULL,
				 ImGuiWindowFlags_NoResize |
					 ImGuiWindowFlags_AlwaysAutoResize |
					 ImGuiWindowFlags_NoMove);

	ImGui::Text("Game Over!");
}
