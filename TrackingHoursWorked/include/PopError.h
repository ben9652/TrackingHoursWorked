#ifndef __POP_ERROR
#define __POP_ERROR
#include "imgui.h"
#include "Layer.h"
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include "common.h"

class PopError : public Layer
{
public:
	PopError(const char8_t* msg, bool* ventanaActiva)
	{
		message = (char*)malloc(300);
		memset(message, 0, 300);
		size_t sizeMsg = 0;
		for (char8_t* c = (char8_t*)msg; *c != 0; c++)
			sizeMsg++;
		for (int i = 0; i < sizeMsg; i++)
			message[i] = msg[i];

		enterPresionado = true;
		this->ventanaActiva = ventanaActiva;
	}

	virtual void OnUIRender() override
	{
		ImGui::OpenPopup("Error");

		char* msg_aux = (char*)malloc(300);
		memset(msg_aux, 0, 300);
		strcpy_s(msg_aux, 300, message);

		int cantidad_saltos_de_linea = 0;
		int cantidad_items = 0;
		for (int i = 0; i < strlen(message); i++)
		{
			if (message[i] == '\n')
				cantidad_saltos_de_linea++;
			if (message[i] == '*')
				cantidad_items++;
		}

		char* next_token;
		char* token_linea;
		size_t maxStrSize = 0;
		if (cantidad_saltos_de_linea != 0)
		{
			token_linea = strtok_s(msg_aux, "\n", &next_token);
			while (token_linea != nullptr)
			{
				maxStrSize = std::max<size_t>({ maxStrSize, strlen(token_linea) });
				token_linea = strtok_s(NULL, "\n", &next_token);
			}
		}
		else
			maxStrSize = strlen(message);

		if (!ImGui::GetIO().KeysData[ImGuiKey_Enter].Down)
			enterPresionado = false;

		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImColor(94, 0, 0).Value);
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImColor(170, 0, 0).Value);
		ImGui::PushStyleColor(ImGuiCol_Button, ImColor(130, 0, 0).Value);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor(205, 41, 0).Value);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImColor(255, 0, 0).Value);

		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, 0, ImVec2(0.5f, 0.5f));
		if (cantidad_saltos_de_linea == 0)
			ImGui::SetNextWindowSize(ImVec2((float)maxStrSize * 10 + 5.0f, 0));
		else
			ImGui::SetNextWindowSize(ImVec2((float)maxStrSize * 7 + 5.0f, 70.0f * (float)cantidad_saltos_de_linea));
		if (ImGui::BeginPopupModal("Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
		{
			bool ventanaEnfocada = ImGui::IsWindowFocused();

			if (cantidad_saltos_de_linea != 0)
			{
				memset(msg_aux, 0, 300);
				strcpy_s(msg_aux, 300, message);
				token_linea = strtok_s(msg_aux, "\n", &next_token);;
				if (cantidad_items != 0)
				{
					for (int i = 0; i < cantidad_saltos_de_linea + 1; i++)
					{
						if (token_linea[0] == '*')
						{
							ImGui::Bullet();
							ImGui::Text(token_linea + 1);
						}
						else
							ImGui::Text(token_linea);
						token_linea = strtok_s(NULL, "\n", &next_token);
					}
				}
				else
				{
					for (int i = 0; i < cantidad_saltos_de_linea + 1; i++)
					{
						ImGui::TextCenter(token_linea);
						token_linea = strtok_s(NULL, "\n", &next_token);
					}
				}
			}
			else
			{
				ImGui::Text("");
				ImGui::TextCenter(message);
			}
			ImGui::Text("");
			
			ImGuiKey key = ImGuiKey_Enter;
			ImGuiIO io = ImGui::GetIO();
			bool escapePressed = io.KeysData[ImGuiKey_Escape].Down;
			if (ImGui::ButtonCenteredOnLine("Aceptar") || ventanaEnfocada && (io.KeysData[key].Down && !enterPresionado || escapePressed))
			{
				enterPresionado = true;
				*ventanaActiva = false;
				App& instancia = App::Get();
				ImGui::CloseCurrentPopup();
				instancia.PopLayer();
			}
			ImGui::EndPopup();
		}

		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
	}

private:

	bool* ventanaActiva;
	bool enterPresionado;
	char* message;
};

#endif