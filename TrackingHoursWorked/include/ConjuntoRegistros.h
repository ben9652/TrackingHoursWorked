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
		// Colecci�n que almacena los registros seg�n un tiempo de filtrado ingresado en la opci�n 4 del men� de actividades
		std::vector<Registro> registros_agrupados;
		int idConjuntoRegistros;
	};
}
#endif