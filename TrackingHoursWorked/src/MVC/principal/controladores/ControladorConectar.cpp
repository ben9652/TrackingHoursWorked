#include "ControladorConectar.h"
#include "ControladorPrincipal.h"
#include "VistaConectar.h"
#include "VistaPrincipal.h"
#include "GestorConexion.h"
#include "GestorActividades.h"
#include "GestorRegistros.h"
#include "GestorDatos.h"
#include "ConnectionException.h"
#include "App.h"
#include <stdlib.h>
#include <string.h>
#include "PopError.h"
#include "VistaCarga.h"
#include <ctime>

bool Controller::ControladorConectar::conexion_realizada = false;

Controller::ControladorConectar::ControladorConectar()
{
	user = (char*)malloc(50);
	password = (char*)malloc(100);
	memset(user, 0, 50);
	memset(password, 0, 100);

	App& instanciar = App::Get();
	instanciar.PushLayer(std::make_shared<UI::VistaConectar>(UI::VistaConectar(this)));
}

Controller::ControladorConectar::~ControladorConectar()
{

}

bool Controller::ControladorConectar::intentarConectar(bool* seMuestraError)
{
	App& instancia = App::Get();

	if (strlen(user) == 0 && strlen(password) == 0)
		instancia.PushLayer(std::make_shared<PopError>(PopError(u8"Usuario y contraseña no llenados", seMuestraError)));
	else if (strlen(user) == 0)
		instancia.PushLayer(std::make_shared<PopError>(PopError(u8"Usuario no llenado", seMuestraError)));
	else if (strlen(password) == 0)
		instancia.PushLayer(std::make_shared<PopError>(PopError(u8"Contraseña no llenada", seMuestraError)));
	else
	{
		GestorConexion* gc;
		try {
			gc = GestorConexion::abrirConexion(user, password);
			return true;
		}
		catch (ConnectionException e) {
			instancia.PushLayer(std::make_shared<PopError>(PopError((char8_t*)e.what(), seMuestraError)));
		}
	}
	return false;
}

void Controller::ControladorConectar::recopilarDatos()
{
	App& instancia = App::Get();

	Model::GestorActividades* ga = Model::GestorActividades::instanciar();
	Model::GestorRegistros* gr = Model::GestorRegistros::instanciar();
	Model::GestorDatos* gd = Model::GestorDatos::instanciar();
	GestorConexion* gc = GestorConexion::instanciar();

	sql::ResultSet* res;
	sql::Statement* stmt;

	// Obtengo la cantidad de filas que hay en la tabla Actividades
	stmt = gc->createStatement();
	res = stmt->executeQuery("SELECT COUNT(*) FROM Actividades");
	res->next();
	gd->asignarCantidadActividadesEnBD(res->getUInt(1));

	// Obtengo la cantidad de filas que hay en la tabla Registros
	stmt = gc->createStatement();
	res = stmt->executeQuery("SELECT COUNT(*) FROM Registros;");
	res->next();
	gd->asignarCantidadRegistrosEnBD(res->getUInt(1));

	instancia.PopLayer();
	instancia.ModifyWindowSize(650, 100);
	instancia.PushLayer<UI::VistaCarga>();

	// Obtengo los datos de la base de datos
	ga->Dame();
	gr->Dame();

	// Delay de 2 segundo
	clock_t now = clock();
	while (clock() - now < CLOCKS_PER_SEC * 2);

	instancia.PopLayer();

	delete stmt;
	delete res;
	conexion_realizada = true;
	instancia.SetFlagToClose();
}

Controller::ControladorConectar& Controller::ControladorConectar::operator=(const ControladorConectar& other)
{
	strcpy_s(user, 50, other.user);
	strcpy_s(password, 100, other.password);
	return *this;
}