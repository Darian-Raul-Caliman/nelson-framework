#include "nspch.h"
#include "Theme.h"
#include "imgui.h"

namespace Nelson {


	static ImVec4 Hex(unsigned int rgb, float alpha = 1.0f)
	{
		return ImVec4(
			((rgb >> 16) & 0xFF) / 255.0f,
			((rgb >> 8) & 0xFF) / 255.0f,
			(rgb & 0xFF) / 255.0f,
			alpha);
	}

	void ApplyNelsonTheme()
	{
		ImGui::StyleColorsDark(); 

		ImGuiStyle& style = ImGui::GetStyle();


		style.WindowRounding = 0.0f;
		style.ChildRounding = 0.0f;
		style.FrameRounding = 0.0f;
		style.PopupRounding = 0.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabRounding = 0.0f;
		style.TabRounding = 0.0f;

		style.WindowBorderSize = 1.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupBorderSize = 1.0f;
		style.FrameBorderSize = 1.0f;
		style.TabBorderSize = 1.0f;

		style.WindowPadding = ImVec2(10.0f, 10.0f);
		style.FramePadding = ImVec2(8.0f, 5.0f);
		style.ItemSpacing = ImVec2(10.0f, 7.0f);
		style.ItemInnerSpacing = ImVec2(7.0f, 5.0f);
		style.ScrollbarSize = 14.0f;
		style.GrabMinSize = 12.0f;
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);   

		const ImVec4 night = Hex(0x140B2A);   
		const ImVec4 purple = Hex(0x1E1240);  
		const ImVec4 violet = Hex(0x2E1A5C); 
		const ImVec4 lavender = Hex(0x45287F);   
		const ImVec4 border = Hex(0x7B2FBE);   
		const ImVec4 magenta = Hex(0xFF2E97);   
		const ImVec4 darkPink = Hex(0xB0206A);   
		const ImVec4 cyan = Hex(0x00F0FF);  
		const ImVec4 teal = Hex(0x0B6E8A);   
		const ImVec4 orange = Hex(0xFF9F1C);   
		const ImVec4 yellow = Hex(0xFFE45E);   
		const ImVec4 text = Hex(0xF2E9FF);
		const ImVec4 textDim = Hex(0x8A7AA8);

		ImVec4* c = style.Colors;


		c[ImGuiCol_Text] = text;
		c[ImGuiCol_TextDisabled] = textDim;
		c[ImGuiCol_TextSelectedBg] = Hex(0xFF2E97, 0.35f);


		c[ImGuiCol_WindowBg] = purple;
		c[ImGuiCol_ChildBg] = night;
		c[ImGuiCol_PopupBg] = night;
		c[ImGuiCol_Border] = border;
		c[ImGuiCol_BorderShadow] = Hex(0x000000, 0.0f);
		c[ImGuiCol_MenuBarBg] = night;
		c[ImGuiCol_ModalWindowDimBg] = Hex(0x000000, 0.6f);


		c[ImGuiCol_TitleBg] = night;
		c[ImGuiCol_TitleBgActive] = darkPink;
		c[ImGuiCol_TitleBgCollapsed] = night;


		c[ImGuiCol_FrameBg] = violet;
		c[ImGuiCol_FrameBgHovered] = lavender;
		c[ImGuiCol_FrameBgActive] = Hex(0x5A33A6);


		c[ImGuiCol_Button] = darkPink;
		c[ImGuiCol_ButtonHovered] = magenta;
		c[ImGuiCol_ButtonActive] = orange;

		c[ImGuiCol_Header] = teal;
		c[ImGuiCol_HeaderHovered] = Hex(0x00B8D4);
		c[ImGuiCol_HeaderActive] = cyan;

		c[ImGuiCol_CheckMark] = yellow;
		c[ImGuiCol_SliderGrab] = cyan;
		c[ImGuiCol_SliderGrabActive] = orange;

		c[ImGuiCol_Tab] = violet;
		c[ImGuiCol_TabHovered] = magenta;
		c[ImGuiCol_TabActive] = darkPink;
		c[ImGuiCol_TabUnfocused] = night;
		c[ImGuiCol_TabUnfocusedActive] = violet;

		c[ImGuiCol_Separator] = border;
		c[ImGuiCol_SeparatorHovered] = magenta;
		c[ImGuiCol_SeparatorActive] = cyan;
		c[ImGuiCol_ResizeGrip] = Hex(0x7B2FBE, 0.5f);
		c[ImGuiCol_ResizeGripHovered] = magenta;
		c[ImGuiCol_ResizeGripActive] = cyan;


		c[ImGuiCol_ScrollbarBg] = night;
		c[ImGuiCol_ScrollbarGrab] = violet;
		c[ImGuiCol_ScrollbarGrabHovered] = border;
		c[ImGuiCol_ScrollbarGrabActive] = magenta;


		c[ImGuiCol_DockingPreview] = Hex(0x00F0FF, 0.45f);
		c[ImGuiCol_DockingEmptyBg] = night;

		c[ImGuiCol_TableHeaderBg] = violet;
		c[ImGuiCol_TableBorderStrong] = border;
		c[ImGuiCol_TableBorderLight] = Hex(0x45287F);
		c[ImGuiCol_TableRowBg] = Hex(0x000000, 0.0f);
		c[ImGuiCol_TableRowBgAlt] = Hex(0xFFFFFF, 0.04f);


		c[ImGuiCol_PlotLines] = cyan;
		c[ImGuiCol_PlotLinesHovered] = magenta;
		c[ImGuiCol_PlotHistogram] = orange;
		c[ImGuiCol_PlotHistogramHovered] = yellow;


		c[ImGuiCol_DragDropTarget] = yellow;
		c[ImGuiCol_NavHighlight] = cyan;
		c[ImGuiCol_NavWindowingHighlight] = Hex(0xFFFFFF, 0.7f);
		c[ImGuiCol_NavWindowingDimBg] = Hex(0x000000, 0.5f);
	}
}