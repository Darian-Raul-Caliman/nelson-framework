#include "Nelson/Nelson.h"
#include "imgui.h"

class ExampleLayer : public Nelson::Layer
{
public:
	ExampleLayer() : Layer("Example") {};
	float m_Position = 0.0f;
	float m_LastFrameMs = 0.0f;
	int m_FrameCount = 0;




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
//		ImGui::Text("Pozitie: %.1f", m_Position);
//		ImGui::Text("Frame: %.2f ms", m_LastFrameMs);
//		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
//		ImGui::GetIO().Framerate;
		ImGui::Text("Frame-uri: %d", m_FrameCount);
		ImGui::End();
		ImGui::ShowDemoWindow();
	}


	void OnEvent(Nelson::Event& event) override
	{

	}

	void OnAttach() override {


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