#ifndef __CONTROLADOR_PADRE
#define __CONTROLADOR_PADRE
#include "App.h"

namespace Controller
{
	class ControladorPadre
	{
	public:
		virtual void ejecutarLogica() {};
		static void CerrarError();
	};
}

#endif