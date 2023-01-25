#ifndef __GESTOR_ACTIVIDADES
#define __GESTOR_ACTIVIDADES

#include <vector>
#include "Actividad.h"
#include <string>
#include <unordered_map>

namespace Model
{
	class GestorActividades
	{
	public:
		~GestorActividades();
		static GestorActividades* instanciar();
		size_t cantidadActividades() const;
		Actividad& obtenerActividadPorId(int idActividad);
		Actividad& obtenerActividadPorIndice(int index);

		static size_t cantidad_de_filas_en_bd;

		enum Codigo {
			OK, ACTIVIDAD_EXISTENTE, ACTIVIDAD_INEXISTENTE, ACTIVIDAD_CON_REGISTROS
		};

		sql::ResultSet* CrearActividad(const char* nombreActividad);
		sql::ResultSet* ModificarActividad(int idActividad, const char* nuevoNombre);
		sql::ResultSet* BorrarActividad(int idActividad);
		void Dame();

	private:
		GestorActividades()
		{
		}

		static GestorActividades* gestor;
		std::vector<Actividad> actividades;
		std::unordered_map<int, int> indices;
	};
}

#endif