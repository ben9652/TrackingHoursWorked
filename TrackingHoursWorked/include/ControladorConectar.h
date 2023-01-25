#ifndef __CONTROLADOR_CONECTAR
#define __CONTROLADOR_CONECTAR
#include "ControladorPrincipal.h"
#include "GestorConexion.h"
#include <memory>

namespace Controller
{

	class ControladorConectar
	{
	public:
		ControladorConectar();
		~ControladorConectar();

		bool intentarConectar(bool* seMuestraError);
		void recopilarDatos();

		ControladorConectar& operator=(const ControladorConectar& other);

		char* user;
		char* password;
		static bool conexion_realizada;
	};

}

#endif