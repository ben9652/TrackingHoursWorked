#ifndef __ACTIVIDAD
#define __ACTIVIDAD
#include "GestorConexion.h"
#include <vector>
#include "ConjuntoRegistros.h"
#include <TextTable.h>

namespace Model
{
	class Actividad
	{
	private:
		int idActividad;
		char* nombre;
		unsigned int segundosTotales;
		size_t registrosTotales;
		bool nullFlag;

		std::vector<ConjuntoRegistros> conjuntos_registros_filtrados;
		std::vector<TextTable>* tablasConjuntos;

		// Las horas que representan los segundos totales
		int horas;

		// Los minutos que representan los segundos totales, descontando las horas
		int minutos;

		// Los segundos que representan los segundos totales, descontando las horas y minutos
		int segundos;

		void actualizarHorasMinutosSegundos();

	public:
		Actividad(int idActividad, const char* nombre);
		Actividad(int idActividad, const char* nombre, unsigned int segundosTotales);
		Actividad(int idActividad, const char* nombre, unsigned int segundosTotales, size_t registrosTotales);
		Actividad(const Actividad& other);
		Actividad(Actividad&& other) noexcept;
		Actividad();
		~Actividad();

		Actividad& operator=(const Actividad& other);

		bool listaRegistrosActualizada;

		bool esActividadNula();
		int getIdActividad() const;
		const char* getNombre() const;
		unsigned int getSegundosTotales() const;

		const std::vector<ConjuntoRegistros>& getConjuntosRegistros();
		const std::vector<TextTable>& getTablasConjuntos();
		void actualizarTablas();

		size_t getRegistrosTotales() const;
		void incrementarRegistrosTotales();
		void decrementarRegistrosTotales();
		void reiniciarRegistrosTotales();

		void setIdActividad(int idActividad);
		void setNombre(const char* nombre);
		void setSegundosTotales(unsigned int segundosTotales);

		/// <summary>
		/// Nos ayuda a expresar el tiempo consumido total en horas, minutos y segundos
		/// </summary>
		/// <returns>Cadena de caracteres con tiempo consumido en horas, minutos y segundos</returns>
		const char* getTiempoConsumido();

		/// <summary>
		/// Se modifica el tiempo total de la actividad por el cambio del tiempo de un registro.
		/// </summary>
		/// <param name="tiempoViejo">Es la cantidad de tiempo que un registro tuvo</param>
		/// <param name="tiempoNuevo">Es la cantidad de tiempo nueva a la que quiere actualizar un registro</param>
		void RegistroModificaTiempo(unsigned int tiempoViejo, unsigned int tiempoNuevo);

		int getHoras();
		int getMinutos();
		int getSegundos();

		void agregarConjuntoRegistros(const ConjuntoRegistros& cr);
		void limpiarColeccionConjuntos();
		void agruparRegistros(int tiempoFiltro);
	};
}

#endif