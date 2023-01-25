#include <iostream>
#include "GestorConexion.h"
#include "ConnectionException.h"

const char8_t* GestorConexion::ERROR_DRIVER = u8"No se encontró la librería para el driver de MySQL";

const char8_t* GestorConexion::ABRIR_CONEXION_ERROR = u8"Error al abrir la conexión. Revisar:\n*que esté levantado el servicio\n*que sean correctos el usuario y clave especificados";

const char8_t* GestorConexion::ERROR_CONEXION = u8"Se perdió la conexión con el servidor o base de datos";

const char8_t* GestorConexion::ERROR_STMT = u8"No se pudo preparar la consulta";

const char8_t* GestorConexion::ERROR_CONSULTA = u8"No se pudo hacer la consulta";

const char* GestorConexion::SERVIDOR = "localhost";

const unsigned short GestorConexion::PUERTO = 3306;

const char* GestorConexion::BD = "HorasTrabajadas";

GestorConexion* GestorConexion::gestor;

GestorConexion::GestorConexion(const char* usuario, const char* clave)
{
	this->usuario = usuario;

	sql::ConnectOptionsMap connection_properties;

	connection_properties["hostName"] = SERVIDOR;
	connection_properties["userName"] = usuario;
	connection_properties["password"] = clave;
	connection_properties["schema"] = "HorasTrabajadas";
	connection_properties["port"] = 3306;
	connection_properties["OPT_RECONNECT"] = true;
	
	try {
		driver = get_driver_instance();
		conector = driver->connect(connection_properties);
	}
	catch (sql::SQLException e) {
		throw ConnectionException(ABRIR_CONEXION_ERROR);
	}
}

GestorConexion::~GestorConexion()
{
	if (conector != nullptr)
		cerrarConexion();
}

GestorConexion* GestorConexion::abrirConexion(const char* usuario, const char* clave)
{
	if (gestor == nullptr)
		gestor = new GestorConexion(usuario, clave);
	return gestor;
}

GestorConexion* GestorConexion::instanciar()
{
	return gestor;
}

sql::Statement* GestorConexion::createStatement()
{
	if (conector != nullptr)
		return this->conector->createStatement();
	else
		throw sql::SQLException((char*)ERROR_CONEXION);
}

sql::PreparedStatement* GestorConexion::prepareStatement(const sql::SQLString& sql)
{
	if (conector != nullptr)
		return this->conector->prepareStatement(sql);
	else
		throw sql::SQLException((char*)ERROR_CONEXION);
}

void GestorConexion::cerrarConexion()
{
	if (conector != nullptr)
	{
		this->conector->close();
		this->conector = nullptr;
	}
	else
		throw sql::SQLException((char*)ERROR_CONEXION);
}