#ifndef __VISTA_CARGA
#define __VISTA_CARGA
#include "imgui.h"
#include "Layer.h"
#include "ControladorConectar.h"
#include "GestorDatos.h"
#include "common.h"

namespace UI
{
	class VistaCarga : public Layer
	{
	public:
		virtual void OnUIRender() override
		{
			Model::GestorDatos* gd = Model::GestorDatos::instanciar();
			ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImColor(0, 90, 160).Value);

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
			ImGui::Begin("Cargando datos", nullptr, window_flags);
			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

			float progreso = gd->porcentajeDatosTomados();
			ImGui::ProgressBar(progreso, ImVec2(0.0f, 0.0f));
			ImGui::SameLine();
			ImGui::Text("Datos tomados");
			char buf[50];
			size_t datos_tomados = gd->getDatosTomados();
			size_t datos_totales = gd->getDatosTotales();
			sprintf_s(buf, 50, "%zu/%zu", datos_tomados, datos_totales);
			ImGui::ProgressBar(progreso, ImVec2(0.f, 0.f), buf);
			ImGui::SameLine();
			ImGui::Text("Datos tomados sobre los totales");

			ImGui::PopStyleColor();

			ImGui::End();
		}
	};
}

#endif