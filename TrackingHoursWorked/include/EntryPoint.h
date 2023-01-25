#pragma once
#include "App.h"
#include "ControladorConectar.h"
#include "ControladorPrincipal.h"

#ifdef WL_PLATFORM_WINDOWS

bool g_ApplicationRunning = true;
bool conexion_superada = false;
extern App* CreateApplication(int argc, char** argv);

int Main(int argc, char** argv)
{
	Controller::ControladorConectar* cc = nullptr;
	Controller::ControladorPrincipal* cp = nullptr;

	App* app;
	// Ventana en la que se realiza el log-in y la carga de datos
	app = CreateApplication(argc, argv);
	cc = new Controller::ControladorConectar();
	app->Run();
	delete app;

	if (!Controller::ControladorConectar::conexion_realizada)
		return 0;
	conexion_superada = true;

	// Ventana del programa principal
	app = CreateApplication(argc, argv);
	delete cc;
	cp = new Controller::ControladorPrincipal();
	app->Run();
	delete app;

	delete cp;

	return 0;
}

#ifdef WL_DIST

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Main(argc, argv);
}

#endif // WL_DIST

#endif // WL_PLATFORM_WINDOWS
