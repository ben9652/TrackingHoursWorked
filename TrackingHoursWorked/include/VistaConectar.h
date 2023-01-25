#ifndef __VISTA_CONECTAR
#define __VISTA_CONECTAR
#include "imgui.h"
#include "Layer.h"
#include "ControladorConectar.h"

namespace UI
{

	class VistaConectar : public Layer
	{
	private:
		Controller::ControladorConectar* controlador;
		bool enterPresionado;
		bool mostrandoError;
		bool conexion_exitosa;
	public:
		VistaConectar(Controller::ControladorConectar* _controlador);

		VistaConectar& operator=(const VistaConectar& other);

		virtual void OnUIRender() override;
	};

}

#endif