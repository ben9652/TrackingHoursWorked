#ifndef _GESTOR_DATOS_
#define _GESTOR_DATOS_

namespace Model
{
	class GestorDatos
	{
	public:

		static GestorDatos* instanciar();

		size_t getDatosTotales();
		size_t getDatosTomados();

		float porcentajeDatosTomados();

		void asignarCantidadActividadesEnBD(size_t cantidadActividades);
		void asignarCantidadRegistrosEnBD(size_t cantidadRegistros);

		void asignarCantidadActividades(size_t cantidadActividades);
		void asignarCantidadRegistros(size_t cantidadActividades);

		void agregar_ActividadEnBD();
		void agregar_RegistroEnBD();

		void tomarActividad();
		void tomarRegistro();

		void eliminar_ActividadEnBD();
		void eliminar_RegistroEnBD();

		size_t obtenerCantidadActividadesEnBD();
		size_t obtenerCantidadRegistrosEnBD();

		size_t obtenerCantidadActividades();
		size_t obtenerCantidadRegistros();


	private:
		GestorDatos()
		{
			datos_totales = 0;
			datos_tomados = 0;
			cantidad_actividades_en_bd = 0;
			cantidad_registros_en_bd = 0;

			actividades_tomadas = 0;
			registros_tomados = 0;
		}

		static GestorDatos* gestor;

		// Esta es la cantidad total de datos que hay en la base de datos
		size_t datos_totales;

		// Esta es la cantidad de datos que hay actualmente en el programa
		size_t datos_tomados;

		size_t cantidad_actividades_en_bd;
		size_t cantidad_registros_en_bd;

		size_t actividades_tomadas;
		size_t registros_tomados;
	};
}

#endif