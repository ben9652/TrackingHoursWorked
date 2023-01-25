#include "imgui.h"
#include "EntryPoint.h"

class ExampleLayer : public Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		if (ImGui::Button("Button"))
		{
			App& inst = App::Get();
			inst.PopLayer();
		}
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

class SaludoEsp : public Layer
{
public:
	virtual void OnDetach() override
	{
		
	}

	virtual void OnUIRender() override
	{
		if (ImGui::Begin("Hola"))
		{
			ImGui::Text("Este texto est\xc3\xa1 en espa\xc3\xb1ol");
			ImGui::Button("Bot\xc3\xb3n");
		}
		ImGui::End();
	}
};

App* CreateApplication(int argc, char** argv)
{
	App::singleton = new App();
	App& instancia = App::Get();
	return App::singleton;
}