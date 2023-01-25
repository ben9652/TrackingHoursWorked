#ifndef __GESTOR_CONEXION
#define __GESTOR_CONEXION

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

class GestorConexion
{
public:
	~GestorConexion();

	static const char8_t* ERROR_DRIVER;
	static const char8_t* ABRIR_CONEXION_ERROR;
	static const char8_t* ERROR_CONEXION;
	static const char8_t* ERROR_STMT;
	static const char8_t* ERROR_CONSULTA;

	// Abrir una conexión con el servidor SQL
	static GestorConexion* abrirConexion(const char* usuario, const char* clave);

	static GestorConexion* instanciar();

	// Se crea una instancia del objeto encargado del armado de una consulta SQL
	sql::Statement* createStatement();

	// Esto nos sirve para preparar una consulta de la que no esperamos un resultado
	sql::PreparedStatement* prepareStatement(const sql::SQLString& sql);

	// Cerrar la conexión con el servidor SQL
	void cerrarConexion();

private:
	GestorConexion(const char* usuario, const char* clave);

	static const char* SERVIDOR;
	static const unsigned short PUERTO;
	static const char* BD;
	const char* usuario;

	static GestorConexion* gestor;
	sql::Connection* conector;
	sql::Driver* driver;
};

#endif