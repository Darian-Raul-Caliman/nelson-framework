#include "Nelson/Nelson.h"
#include "imgui.h"


using namespace Nelson;
using namespace ImGui;

class ExampleLayer : public Layer
{
public:
	void OnUIRender() override
	{
		Begin("Example");

		Text("Hello from Nelson!");

		if (Button("Click me"))
			m_Clicks++;

		Text("Clicks: %d", m_Clicks);

		End();
	}

private:
	int m_Clicks = 0;
};

Application* Nelson::CreateApplication()
{
	ApplicationSpecification spec;
	spec.Name = "MyApp";

	auto* app = new Application(spec);
	app->PushLayer<ExampleLayer>();
	return app;
}