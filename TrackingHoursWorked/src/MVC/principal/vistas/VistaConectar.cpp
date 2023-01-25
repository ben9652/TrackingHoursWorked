#include "VistaConectar.h"
#include "common.h"
#include <thread>

UI::VistaConectar::VistaConectar(Controller::ControladorConectar* _controlador)
{
	controlador = _controlador;
	enterPresionado = true;
	mostrandoError = false;
	conexion_exitosa = false;
}

UI::VistaConectar& UI::VistaConectar::operator=(const VistaConectar& other)
{
	controlador = other.controlador;
	return *this;
}

void UI::VistaConectar::OnUIRender()
{
	const char8_t* texto_pass = u8"Contraseña   ";
	ImGui::Begin("Log-in", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	//ImGui::SetWindowSize(ImVec2(400.0f, 100.0f));
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

	ImGui::TextCenter("Usuario     ");
	ImGui::PushItemWidth(512);
	ImGui::InputText("##user", controlador->user, 50);
	ImGui::PopItemWidth();
	ImGui::Text("");
	ImGui::Text("");

	ImGui::TextCenter((char*)texto_pass);
	ImGui::PushItemWidth(512);
	ImGui::InputText("##password", controlador->password, 100, ImGuiInputTextFlags_Password);
	ImGui::PopItemWidth();
	ImGui::Text("");
	const char8_t* texto_iniciar_sesion = u8"Iniciar sesión";

	if (controlador->conexion_realizada)
		delete controlador;

	if (!mostrandoError)
	{
		if (!ImGui::GetIO().KeysData[ImGuiKey_Enter].Down)
			enterPresionado = false;

		bool ventanaEnfocada = ImGui::IsWindowFocused();

		ImGuiKey key = ImGuiKey_Enter;
		ImGuiIO& io = ImGui::GetIO();
		if (ImGui::ButtonCenteredOnLine((char*)texto_iniciar_sesion) || ventanaEnfocada && io.KeysData[key].Down && !enterPresionado)
		{
			mostrandoError = true;
			enterPresionado = true;
			if (!conexion_exitosa)
			{
				if (controlador->intentarConectar(&mostrandoError))
				{
					conexion_exitosa = true;
					std::thread* hiloRecopilacion = new std::thread(&Controller::ControladorConectar::recopilarDatos, controlador);
				}
			}
		}
	}
	ImGui::End();
}