#ifndef __GESTOR_REGISTROS
#define __GESTOR_REGISTROS

#include <vector>
#include "Registro.h"
#include "ControladorPrincipal.h"
#include "GestorConexion.h"
#include <unordered_map>
#include <array>

namespace std
{
	struct par_hash {
		size_t operator()(const array<int, 2>& v) const
		{
			std::size_t h = 0;

			for (const int& elem : v)
				h ^= std::hash<int>{}(elem)+0x9e3779b9 + (h << 6) + (h >> 2);

			return h;
		}
	};
}

namespace Model
{
	class GestorRegistros
	{
	public:
		~GestorRegistros();
		static GestorRegistros* instanciar();
		size_t cantidadRegistros();
		size_t cantidadRegistrosPorActividad(int idActividad);
		Registro& obtenerRegistroPorId(int idRegistro, int idActividad);
		Registro& obtenerRegistroPorIndice(int index);

		static size_t cantidad_de_filas_en_bd;

		// Estos métodos que vienen a continuación serán los equivalentes a los
		// procedimientos almacenados de la base de datos asociados a los registros.
		// 
		// Aquellos procedimientos almacenados que afectan a los datos de la tabla,
		// devolverán solamente una cadena de caracteres, pero aquellos que corresponden
		// a consultas de datos, devolverán el gestor de conexión así el controlador
		// pueda manipular la muestra de dichos datos.

		void AgregarRegistro(int idActividad, unsigned int segundosConsumidos, const char* descripcion);
		sql::ResultSet* EliminarRegistro(int idRegistro, int idActividad);
		sql::ResultSet* BuscarRegistro(int idRegistro, int idActividad, const char* criterioTiempo, unsigned int segundosConsumidos, const char* criterioFecha, const char* fecha, const char* descripcion);

		void Dame();

	private:
		GestorRegistros()
		{

		}

		static GestorRegistros* gestor;
		std::vector<Registro> registros;
		std::unordered_map<std::array<int, 2>, int, std::par_hash> indices;
	};
}

#endif