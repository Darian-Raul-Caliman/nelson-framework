#include "Nelson/Nelson.h"
#include "imgui.h"

class ExampleLayer : public Nelson::Layer
{
public:
	ExampleLayer() : Layer("Example") {};
	float m_Position = 0.0f;
	float m_LastFrameMs = 0.0f;
	void OnUpdate(Nelson::Timestep ts) override{
//		m_LastFrameMs = ts.GetMilliseconds();
//		if (Nelson::Input::IsKeyPressed(Nelson::Key::Right))
//			m_Position += 100.0f * ts;
//		if (Nelson::Input::IsKeyPressed(Nelson::Key::Space))
//			m_Position -= 100.0f * ts;
	}

	void OnUIRender() override {
		ImGui::Begin("Nume fereastra");
		ImGui::Text("Nelson Engine");
		ImGui::Button("Click here");
//		ImGui::Text("Pozitie: %.1f", m_Position);
//		ImGui::Text("Frame: %.2f ms", m_LastFrameMs);
//		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
//		ImGui::GetIO().Framerate;
		ImGui::End();
		ImGui::ShowDemoWindow();
	}

	void OnEvent(Nelson::Event& event) override
	{

	}



};


class Sandbox : public Nelson::Application {


public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {
	}
};

Nelson::Application* Nelson::CreateApplication() {
	return new Sandbox();
}