#include "Nelson/Nelson.h"
#include "imgui.h"

class ExampleLayer : public Nelson::Layer
{
public:
	ExampleLayer() : Layer("Example") {};
	float m_Position = 0.0f;
	float m_LastFrameMs = 0.0f;
	int m_FrameCount = 0;
	bool m_ShowDemo = true;
	float m_Volume = 0.5f;


	void OnUpdate(Nelson::Timestep ts) override{
//		m_LastFrameMs = ts.GetMilliseconds();
//		if (Nelson::Input::IsKeyPressed(Nelson::Key::Right))
//			m_Position += 100.0f * ts;
//		if (Nelson::Input::IsKeyPressed(Nelson::Key::Space))
//			m_Position -= 100.0f * ts;
		m_FrameCount += 1;

	}

	void OnUIRender() override {
		ImGui::Begin("Nume fereastra");
		ImGui::Text("Nelson Engine");
		ImGui::Checkbox("Arata demo", &m_ShowDemo);
		ImGui::SliderFloat("Volum", &m_Volume, 0.0f, 1.0f);
		ImGui::Text("Frame-uri: %d", m_FrameCount);
		ImGui::End();

		if (m_ShowDemo)
			ImGui::ShowDemoWindow();
	}


	void OnEvent(Nelson::Event& event) override
	{

	}

	void OnAttach() override {
		auto& settings = Nelson::Application::Get().GetSettings();
		m_ShowDemo = settings.Get("showDemo", true);
		m_Volume = settings.Get("volume", 0.5f);


	}

	void OnDetach() override {
		auto& settings = Nelson::Application::Get().GetSettings();
		settings.Set("showDemo", m_ShowDemo);
		settings.Set("volume", m_Volume);
	}



};


class Sandbox : public Nelson::Application {


public:
	Sandbox(const Nelson::ApplicationSpecification& spec) : Application(spec) {
		SetUpdateMode(Nelson::UpdateMode::Continuous); // Continuous or OnDemand

		PushLayer(new ExampleLayer());
	}
	~Sandbox() {
	}
};

Nelson::Application* Nelson::CreateApplication() {

	Nelson::ApplicationSpecification spec;
	spec.Name = "Any Engine";
	Sandbox* app = new Sandbox(spec);

	app->SetMenubarCallback([app]()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
					app->Close();
				ImGui::EndMenu();
			}
		});
	return app;
}