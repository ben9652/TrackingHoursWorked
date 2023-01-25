#include "Registro.h"
#include <string.h>
#include <stdlib.h>
#include <utility>
#include "common.h"

void Model::Registro::actualizarHorasMinutosSegundos()
{
	horas = segundosConsumidos / 3600;

	minutos = segundosConsumidos % 3600;

	segundos = minutos % 60;

	minutos /= 60;
}

Model::Registro::Registro(int idRegistro, int idActividad, unsigned int segundosConsumidos, tm* fechaCreacion, const char* descripcion)
{
	this->idRegistro = idRegistro;
	this->idActividad = idActividad;
	this->segundosConsumidos = segundosConsumidos;
	this->fechaCreacion = (tm*)malloc(sizeof(tm));
	this->fechaCreacion = fechaCreacion;
	this->descripcion = (char*)malloc(256);
	strcpy_s(this->descripcion, 256, descripcion);
	this->nullFlag = false;

	actualizarHorasMinutosSegundos();
}

Model::Registro::Registro(const Registro& other) noexcept
{
	idRegistro = other.idRegistro;
	idActividad = other.idActividad;
	segundosConsumidos = other.segundosConsumidos;
	fechaCreacion = (tm*)malloc(sizeof(tm));
	fechaCreacion->tm_year = other.fechaCreacion->tm_year;
	fechaCreacion->tm_mon = other.fechaCreacion->tm_mon;
	fechaCreacion->tm_mday = other.fechaCreacion->tm_mday;
	fechaCreacion->tm_hour = other.fechaCreacion->tm_hour;
	fechaCreacion->tm_min = other.fechaCreacion->tm_min;
	fechaCreacion->tm_sec = other.fechaCreacion->tm_sec;
	descripcion = (char*)malloc(256);
	strcpy_s(descripcion, 256, other.descripcion);
	this->nullFlag = false;

	actualizarHorasMinutosSegundos();
}

Model::Registro::Registro(Registro&& other) noexcept
{
	idRegistro = other.idRegistro;
	idActividad = other.idActividad;
	segundosConsumidos = other.segundosConsumidos;
	fechaCreacion = (tm*)malloc(sizeof(tm));
	memcpy(fechaCreacion, other.fechaCreacion, sizeof(tm));
	descripcion = (char*)malloc(256);
	strcpy_s(descripcion, 256, other.descripcion);
	this->nullFlag = false;

	actualizarHorasMinutosSegundos();
}

Model::Registro::Registro()
{
	nullFlag = true;
}

Model::Registro::~Registro()
{
	idRegistro = 0;
	idActividad = 0;
	segundosConsumidos = 0;
	horas = 0;
	minutos = 0;
	segundos = 0;
	free(fechaCreacion);
	fechaCreacion = nullptr;
	free(descripcion);
	descripcion = nullptr;
}

bool Model::Registro::esRegistroNulo()
{
	return nullFlag;
}

int Model::Registro::getIdRegistro() const
{
	return idRegistro;
}

int Model::Registro::getIdActividad() const
{
	return idActividad;
}

unsigned int Model::Registro::getSegundosConsumidos() const
{
	return segundosConsumidos;
}

tm* Model::Registro::getFechaCreacion() const
{
	return fechaCreacion;
}

const char* Model::Registro::getDescripcion() const
{
	return descripcion;
}

const char* Model::Registro::getIdRegistroString() const
{
	char* idRegistro = (char*)malloc(20);
	_itoa_s(this->idRegistro, idRegistro, 20, 10);
	return idRegistro;
}

const char* Model::Registro::getIdActividadString() const
{
	char* idActividad = (char*)malloc(20);
	_itoa_s(this->idActividad, idActividad, 20, 10);
	return idActividad;
}

const char* Model::Registro::getSegundosConsumidosString() const
{
	char* segundosConsumidos = (char*)malloc(20);
	_itoa_s(this->segundosConsumidos, segundosConsumidos, 20, 10);
	strcat_s(segundosConsumidos, 20, " segundos");
	return segundosConsumidos;
}

const char* Model::Registro::getTiempoConsumido() const
{
	char* tiempo = (char*)malloc(60);
	memset(tiempo, 0, 60);

	if (segundosConsumidos == 0)
		return "0s";

	if (horas != 0)
	{
		char* horas = (char*)malloc(20);
		_itoa_s(this->horas, horas, 20, 10);
		strcat_s(tiempo, 60, horas);
		strcat_s(tiempo, 60, "h ");
	}

	if (minutos != 0)
	{
		char* minutos = (char*)malloc(20);
		_itoa_s(this->minutos, minutos, 20, 10);
		strcat_s(tiempo, 60, minutos);
		strcat_s(tiempo, 60, "m ");
	}

	if (segundos != 0)
	{
		char* segundos = (char*)malloc(20);
		_itoa_s(this->segundos, segundos, 20, 10);
		strcat_s(tiempo, 60, segundos);
		strcat_s(tiempo, 60, "s");
	}

	return tiempo;
}

const char* Model::Registro::getFechaCreacionString() const
{
	char* fechaCreacion = (char*)malloc(20);
	memset(fechaCreacion, 0, 20);

	char* dia = (char*)malloc(3);
	if (this->fechaCreacion->tm_mday < 10)
	{
		dia[0] = '0';
		_itoa_s(this->fechaCreacion->tm_mday, dia + 1, 2, 10);
	}
	else
		_itoa_s(this->fechaCreacion->tm_mday, dia, 3, 10);

	char* mes = (char*)malloc(3);
	if (this->fechaCreacion->tm_mon < 10)
	{
		mes[0] = '0';
		_itoa_s(this->fechaCreacion->tm_mon, mes + 1, 2, 10);
	}
	else
		_itoa_s(this->fechaCreacion->tm_mon, mes, 3, 10);

	char* anio = (char*)malloc(5);
	_itoa_s(this->fechaCreacion->tm_year + 1900, anio, 5, 10);

	char* hora = (char*)malloc(3);
	if (this->fechaCreacion->tm_hour < 10)
	{
		hora[0] = '0';
		_itoa_s(this->fechaCreacion->tm_hour, hora + 1, 2, 10);
	}
	else
		_itoa_s(this->fechaCreacion->tm_hour, hora, 3, 10);

	char* minutos = (char*)malloc(3);
	if (this->fechaCreacion->tm_min < 10)
	{
		minutos[0] = '0';
		_itoa_s(this->fechaCreacion->tm_min, minutos + 1, 2, 10);
	}
	else
		_itoa_s(this->fechaCreacion->tm_min, minutos, 3, 10);

	char* segundos = (char*)malloc(3);
	if (this->fechaCreacion->tm_sec < 10)
	{
		segundos[0] = '0';
		_itoa_s(this->fechaCreacion->tm_sec, segundos + 1, 2, 10);
	}
	else
		_itoa_s(this->fechaCreacion->tm_sec, segundos, 3, 10);

	strcat_s(fechaCreacion, 20, dia);
	strcat_s(fechaCreacion, 20, "/");
	strcat_s(fechaCreacion, 20, mes);
	strcat_s(fechaCreacion, 20, "/");
	strcat_s(fechaCreacion, 20, anio);
	strcat_s(fechaCreacion, 20, " ");
	strcat_s(fechaCreacion, 20, hora);
	strcat_s(fechaCreacion, 20, ":");
	strcat_s(fechaCreacion, 20, minutos);
	strcat_s(fechaCreacion, 20, ":");
	strcat_s(fechaCreacion, 20, segundos);

	return fechaCreacion;
}

void Model::Registro::setIdRegistro(int idRegistro)
{
	this->idRegistro = idRegistro;
}

void Model::Registro::setIdActividad(int idActividad)
{
	this->idActividad = idActividad;
}

void Model::Registro::setSegundosConsumidos(unsigned int segundosConsumidos)
{
	this->segundosConsumidos = segundosConsumidos;

	actualizarHorasMinutosSegundos();
}

void Model::Registro::setFechaCreacion(tm* fechaCreacion)
{
	this->fechaCreacion = fechaCreacion;
}

void Model::Registro::setDescripcion(const char* descripcion)
{
	strcpy_s(this->descripcion, 256, descripcion);
}

void Model::Registro::ModificarTiempo(unsigned int segundosConsumidos)
{
	GestorConexion* gc = GestorConexion::instanciar();
	sql::PreparedStatement* pstmt = gc->prepareStatement("CALL ModificarTiempoConsumido(?,?,?,@m)");
	pstmt->setInt(1, this->idRegistro);
	pstmt->setInt(2, this->idActividad);
	pstmt->setUInt(3, segundosConsumidos);
	pstmt->execute();
	delete pstmt;

	this->segundosConsumidos = segundosConsumidos;
	actualizarHorasMinutosSegundos();
}

void Model::Registro::ModificarDescripcion(const char* descripcion)
{
	GestorConexion* gc = GestorConexion::instanciar();
	sql::PreparedStatement* pstmt = gc->prepareStatement("CALL ModificarDescripcion(?,?,?,@m)");
	pstmt->setInt(1, this->idRegistro);
	pstmt->setInt(2, this->idActividad);
	pstmt->setString(3, descripcion);
	pstmt->execute();
	delete pstmt;

	strcpy_s(this->descripcion, 256, descripcion);
}

int Model::Registro::getHoras()
{
	return horas;
}

int Model::Registro::getMinutos()
{
	return minutos;
}

int Model::Registro::getSegundos()
{
	return segundos;
}
