
#include "nspch.h"
#include "Theme.h"
#include "imgui.h"

namespace Nelson {

	void ApplyNelsonTheme()
	{
		ImGuiStyle& style = ImGui::GetStyle();


		style.WindowRounding = 4.0f;
		style.FrameRounding = 3.0f;
		ImVec4* colors = ImGui::GetStyle().Colors;


		colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.12f, 1.00f);

	}
}