#include "VistaPrincipal.h"

UI::VistaPrincipal::VistaPrincipal(Controller::ControladorPrincipal* _controlador)
{
	controlador = _controlador;
}

UI::VistaPrincipal& UI::VistaPrincipal::operator=(const UI::VistaPrincipal& other)
{
	controlador = other.controlador;
	return *this;
}