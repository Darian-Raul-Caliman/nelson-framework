#include "Nelson/Nelson.h"
#include "imgui.h"

class ExampleLayer : public Nelson::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnAttach() override
	{
	}

	void OnDetach() override
	{
	}

	void OnUpdate(Nelson::Timestep ts) override
	{
	}

	void OnUIRender() override
	{
		ImGui::Begin("Sandbox");
		ImGui::Text("Nelson Engine");
		ImGui::End();
	}

	void OnEvent(Nelson::Event& event) override
	{
	}
};

class Sandbox : public Nelson::Application
{
public:
	Sandbox(const Nelson::ApplicationSpecification& spec)
		: Application(spec)
	{
		PushLayer(new ExampleLayer());
	}
};

Nelson::Application* Nelson::CreateApplication()
{
	Nelson::ApplicationSpecification spec;
	spec.Name = "Any Engine";
	spec.Mode = Nelson::UpdateMode::OnDemand;

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