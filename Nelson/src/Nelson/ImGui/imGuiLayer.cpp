#include "nspch.h"
#include "imGuiLayer.h"
#include <glad/glad.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include "Nelson/Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Nelson/Application.h"


namespace Nelson {

	ImGuiLayer::ImGuiLayer() :Layer("ImGuiLayer")
	{
		

	}
	ImGuiLayer::~ImGuiLayer()
	{

	}


	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(0,ImGuiDockNodeFlags_PassthruCentralNode);
	}

	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupContext);
		}
	}

	void ImGuiLayer::OnAttach()
	{

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGuiStyle& style = ImGui::GetStyle();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}


		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}


	void ImGuiLayer::OnDetach()
	{

		ImGui_ImplOpenGL3_Shutdown();

		
		ImGui_ImplGlfw_Shutdown();

		ImGui::DestroyContext();

	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

	}


}
