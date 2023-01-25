#ifndef __VISTA_PRINCIPAL
#define __VISTA_PRINCIPAL
#include "imgui.h"
#include "Layer.h"
#include "ControladorPrincipal.h"
#include "common.h"

namespace UI
{

	class VistaPrincipal : public Layer
	{
	private:
		Controller::ControladorPrincipal* controlador;
	public:
		VistaPrincipal(Controller::ControladorPrincipal* _controlador);

		VistaPrincipal& operator=(const VistaPrincipal& other);

		virtual void OnUIRender() override
		{
			ImGui::Begin("Programa principal", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
			ImGui::Text("Programa corriendo");
			ImGui::End();
		}
	};

}

#endif