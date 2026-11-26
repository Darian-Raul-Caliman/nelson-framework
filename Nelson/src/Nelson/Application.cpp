#include "nspch.h"
#include "Application.h"
#include "Nelson/FileDialog.h"
#include "Layer.h"
#include "Input.h"
#include "Nelson/Log.h"
#include "Timestep.h"
#include "imgui.h"
#include <glad/GLAD.h>
#include "Nelson/Timer.h"
#include "Nelson/ActionRegistry.h"
#include "Nelson/Platform/PlatformUtils.h"

namespace Nelson {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& spec ) {
		NS_CORE_ASSERT(!s_Instance, "Application already exists ! ");
		m_Specification = spec;
		m_timestamp = std::chrono::steady_clock::now();
		s_Instance = this;
		m_Settings.Load(GetUserDataPath(m_Specification.Name) / "settings.json");
		WindowProps props(m_Specification.Name, m_Specification.Width, m_Specification.Height);
		m_Window = std::unique_ptr<Window>(Window::Create(props));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::onEvent));
		m_Window->SetVSync(m_Specification.VSync);
		FileDialog::Init();;
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {

	}
	
	void Application::SetUpdateMode(UpdateMode mode) {
		m_Specification.Mode = mode;
		m_Window->SetWaitForEvents(mode == UpdateMode::OnDemand);
	}


	void Application::PushLayer(Layer* layer)
	{
		auto op = [this, layer] { m_LayerStack.PushLayer(layer); layer->OnAttach(); };
		if (m_InLoop) m_PendingLayerOps.push_back(op);   // in timpul buclei -> amanat
		else op();                                       // inainte de Run (CreateApplication) -> imediat
	}

	void Application::PushOverlay(Layer* layer)
	{
		auto op = [this, layer] { m_LayerStack.PushOverlay(layer); layer->OnAttach(); };
		if (m_InLoop) m_PendingLayerOps.push_back(op);
		else op();
	}

	void Application::PopLayer(Layer* layer)
	{
		auto op = [this, layer] { m_LayerStack.PopLayer(layer); layer->OnDetach(); delete layer; };
		if (m_InLoop) m_PendingLayerOps.push_back(op);
		else op();
	}

	void Application::ProcessPendingLayerOps()
	{
		while (!m_PendingLayerOps.empty())
		{
			auto ops = std::move(m_PendingLayerOps);
			m_PendingLayerOps.clear();
			for (auto& op : ops)
				op();
		}
	}

	void Application::RequestClose()
	{
		for (Layer* layer : m_LayerStack)
			if (!layer->OnCloseRequested())
				return;        
		Close();
	}

	void Application::Close() {
		m_Running = false;
	}

	Settings& Application::GetSettings()
	{
		return m_Settings;
	}


	void Application::onEvent(Event& e) {

		EventDispatcher dispatcher(e);
		//NS_CORE_INFO("{0}", e); Logging events in the console
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		//NS_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
			{
				break;
			}
		}

	}


	UpdateMode Application::GetUpdateMode() const
	{
		return m_Specification.Mode;
	}

	const ApplicationSpecification& Application::GetSpecification() const
	{
		return m_Specification;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		RequestClose();
		return true;
	}

	void Application::Run() {
		


		m_InLoop = true;
		while (m_Running) {

			ProcessPendingLayerOps();

			auto now = std::chrono::steady_clock::now();
			Timestep ts = std::chrono::duration<float>(now - m_timestamp).count();
			m_timestamp = now;
			// daca trece timestampul de 100 ms se seteaza ca fiind acela 
			if (ts > 0.1f)
				ts = 0.1f;

			//glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(ts);
			}		

			Timer::Update();
			m_ImGuiLayer->Begin();

			if (ImGui::BeginMainMenuBar())
			{
				if (m_MenubarCallback)
					m_MenubarCallback();
				else if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Exit"))
						Close();
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}

			if (m_Specification.EnableDockspace)
				ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);


			for (Layer* layer : m_LayerStack)
				layer->OnUIRender();

			m_ImGuiLayer->End();




				

			m_Window->SetMaxWaitTime(Timer::GetTimeUntilNext());   
			m_Window->OnUpdate();
		}

		m_InLoop = false;
		ProcessPendingLayerOps();       
		m_LayerStack.Clear();
		Timer::CancelAll();
		FileDialog::Shutdown();
		m_ImGuiLayer = nullptr;
		m_Settings.Save();

	}

}
