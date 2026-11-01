#include "Nelson/Nelson.h"
#include "imgui.h"

class ExampleLayer : public Nelson::Layer
{
public:
	ExampleLayer() : Layer("Example") {};


	void OnUIRender() override {
		ImGui::Begin("Nume fereastra");
		ImGui::Text("Nelson Engine");
		ImGui::Button("Click here");
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