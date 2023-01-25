#include "ControladorPrincipal.h"
#include "VistaPrincipal.h"
#include "App.h"

extern bool g_ApplicationRunning;

Controller::ControladorPrincipal::ControladorPrincipal()
{
	App& instancia = App::Get();
	instancia.PushLayer(std::make_shared<UI::VistaPrincipal>(UI::VistaPrincipal(this)));
}

Controller::ControladorPrincipal::~ControladorPrincipal()
{
	g_ApplicationRunning = false;
}