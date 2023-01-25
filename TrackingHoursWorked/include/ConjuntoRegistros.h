#ifndef __CONJUNTO_REGISTROS
#define __CONJUNTO_REGISTROS
#include <vector>
#include "Registro.h"

namespace Model
{
	class ConjuntoRegistros
	{
	public:
		ConjuntoRegistros(int idConjuntoRegistros, const std::vector<Registro>& registros_agrupados);

		int getIdConjuntoRegistros() const;
		const std::vector<Registro>& getConjuntoRegistros() const;

		void setIdConjuntoRegistros(int idConjuntoRegistros);

	private:
		// Colección que almacena los registros según un tiempo de filtrado ingresado en la opción 4 del menú de actividades
		std::vector<Registro> registros_agrupados;
		int idConjuntoRegistros;
	};
}
#endif