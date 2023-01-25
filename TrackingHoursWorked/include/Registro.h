#include <time.h>
#include <GestorConexion.h>

#ifndef __REGISTRO
#define __REGISTRO

namespace Model
{
	class Registro
	{
	private:
		int idRegistro;
		int idActividad;
		unsigned int segundosConsumidos;
		tm* fechaCreacion;
		char* descripcion;
		bool nullFlag;

		int horas;
		int minutos;
		int segundos;

		void actualizarHorasMinutosSegundos();

	public:
		Registro(int idRegistro, int idActividad, unsigned int segundosConsumidos, tm* fechaCreacion, const char* descripcion);
		Registro(const Registro& other) noexcept;
		Registro(Registro&& other) noexcept;
		Registro();
		~Registro();

		bool esRegistroNulo();
		int getIdRegistro() const;
		int getIdActividad() const;
		unsigned int getSegundosConsumidos() const;
		tm* getFechaCreacion() const;
		const char* getDescripcion() const;

		const char* getIdRegistroString() const;
		const char* getIdActividadString() const;
		const char* getSegundosConsumidosString() const;

		/// <summary>
		/// Nos ayuda a expresar el tiempo total consumido en horas, minutos, y segundos
		/// </summary>
		/// <returns>Tiempo total consumido en horas, minutos, y segundos</returns>
		const char* getTiempoConsumido() const;
		const char* getFechaCreacionString() const;

		void setIdRegistro(int idRegistro);
		void setIdActividad(int idActividad);
		void setSegundosConsumidos(unsigned int segundosConsumidos);
		void setFechaCreacion(tm* fechaCreacion);
		void setDescripcion(const char* descripcion);

		void ModificarTiempo(unsigned int segundosConsumidos);
		void ModificarDescripcion(const char* descripcion);

		int getHoras();
		int getMinutos();
		int getSegundos();

		Registro& operator=(const Registro& other) = default;
	};
}
#endif