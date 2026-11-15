#include "Nelson/Nelson.h"
#include "imgui.h"

class ExampleLayer : public Nelson::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnAttach() override
	{
		ImGui::CreateContext();
		ImFontConfig fontConfig;
		fontConfig.OversampleH = 1;
		fontConfig.OversampleV = 1;
		fontConfig.PixelSnapH = true;
		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF,
			0x0100, 0x017F,
			0x0218, 0x021B,
			0,
		};

		ImGuiIO& io = ImGui::GetIO();
		io.FontDefault = io.Fonts->AddFontFromMemoryCompressedTTF(
			PixelifySans_compressed_data, PixelifySans_compressed_size, 16.0f, &fontConfig, ranges);
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
		ImGui::Text(" Mesaj ");
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