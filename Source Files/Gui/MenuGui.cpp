#include "../../Header Files/Gui/MenuGui.h"
#include "../../Header Files/Parameters.h"

#include <stdexcept>

MenuGui::MenuGui(fvec3 *clearColorRef, bool *startGameRef, float bestScore)
	: IGui(),
	  clearColorRef(clearColorRef),
	  startGameRef(startGameRef),
	  bestScore(bestScore)
{
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

	difficultyWindow(10, 10);

	// Ends the ImGui frame declaration.
	ImGui::End();
	// Renders the ImGui frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MenuGui::difficultyWindow(float xpos, float ypos)
{
	ImGui::SetNextWindowPos(ImVec2(xpos, ypos), ImGuiCond_Always);
	ImGui::Begin("Strikers", nullptr,
				 ImGuiWindowFlags_NoResize |
					 ImGuiWindowFlags_NoCollapse |
					 ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Best Score: %.0f", this->bestScore);
	ImGui::Separator();
	static int difficulty = 0;
	ImGui::Text("Select Difficulty:");
	ImGui::RadioButton("Easy", &difficulty, 0);
	ImGui::SameLine();
	ImGui::RadioButton("Medium", &difficulty, 1);
	ImGui::SameLine();
	ImGui::RadioButton("Hard", &difficulty, 2);

	if (ImGui::Button("Start"))
	{
		switch (difficulty)
		{
		case 0:
			Parameters::applyEasy();
			break;
		case 1:
			Parameters::applyMedium();
			break;
		case 2:
			Parameters::applyHard();
			break;
		default:
			throw new std::runtime_error("Invalid difficulty selected in MenuGui::difficultyWindow");
			break;
		}
		*(this->startGameRef) = true;
	}
}