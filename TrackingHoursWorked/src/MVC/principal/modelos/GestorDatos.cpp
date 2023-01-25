#include "GestorDatos.h"

Model::GestorDatos* Model::GestorDatos::gestor;

Model::GestorDatos* Model::GestorDatos::instanciar()
{
	if (gestor == nullptr)
		gestor = new GestorDatos();
	return gestor;
}

size_t Model::GestorDatos::getDatosTotales()
{
	return datos_totales;
}

size_t Model::GestorDatos::getDatosTomados()
{
	return datos_tomados;
}

float Model::GestorDatos::porcentajeDatosTomados()
{
	float x = datos_tomados * 100 / (float)datos_totales;
	return x;
}

void Model::GestorDatos::asignarCantidadActividadesEnBD(size_t cantidadActividades)
{
	if (datos_totales < cantidad_actividades_en_bd)
		datos_totales = cantidadActividades + cantidad_registros_en_bd;
	else
		datos_totales -= cantidad_actividades_en_bd;
	datos_totales += cantidadActividades;
	cantidad_actividades_en_bd = cantidadActividades;
}

void Model::GestorDatos::asignarCantidadRegistrosEnBD(size_t cantidadRegistros)
{
	if (datos_totales < cantidad_registros_en_bd)
		datos_totales = cantidadRegistros + cantidad_actividades_en_bd;
	else
		datos_totales -= cantidad_registros_en_bd;
	datos_totales += cantidadRegistros;
	cantidad_registros_en_bd = cantidadRegistros;
}

void Model::GestorDatos::asignarCantidadActividades(size_t cantidadActividades)
{
	if (datos_tomados < actividades_tomadas)
		datos_tomados = cantidadActividades + registros_tomados;
	else
		datos_tomados -= actividades_tomadas;
	datos_tomados += cantidadActividades;
	actividades_tomadas = cantidadActividades;
}

void Model::GestorDatos::asignarCantidadRegistros(size_t cantidadRegistros)
{
	if (datos_tomados < registros_tomados)
		datos_tomados = cantidadRegistros + actividades_tomadas;
	else
		datos_tomados -= registros_tomados;
	datos_tomados += cantidadRegistros;
	registros_tomados = cantidadRegistros;
}

void Model::GestorDatos::agregar_ActividadEnBD()
{
	datos_totales++;
	cantidad_actividades_en_bd++;
}

void Model::GestorDatos::agregar_RegistroEnBD()
{
	datos_totales++;
	cantidad_registros_en_bd++;
}

void Model::GestorDatos::tomarActividad()
{
	datos_tomados++;
	actividades_tomadas++;
}

void Model::GestorDatos::tomarRegistro()
{
	datos_tomados++;
	registros_tomados++;
}

void Model::GestorDatos::eliminar_ActividadEnBD()
{
	if (datos_totales > 0)
		datos_totales--;
	if (cantidad_actividades_en_bd > 0)
		cantidad_actividades_en_bd--;
}

void Model::GestorDatos::eliminar_RegistroEnBD()
{
	if (datos_totales > 0)
		datos_totales--;
	if (cantidad_registros_en_bd > 0)
		cantidad_registros_en_bd--;
}

size_t Model::GestorDatos::obtenerCantidadActividadesEnBD()
{
	return cantidad_actividades_en_bd;
}

size_t Model::GestorDatos::obtenerCantidadRegistrosEnBD()
{
	return cantidad_registros_en_bd;
}

size_t Model::GestorDatos::obtenerCantidadActividades()
{
	return actividades_tomadas;
}

size_t Model::GestorDatos::obtenerCantidadRegistros()
{
	return registros_tomados;
}
