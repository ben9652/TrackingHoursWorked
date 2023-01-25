#include "Actividad.h"
#include "GestorRegistros.h"
#include <stdlib.h>
#include <string.h>

void Model::Actividad::actualizarHorasMinutosSegundos()
{
	horas = segundosTotales / 3600;

	minutos = segundosTotales % 3600;

	segundos = minutos % 60;

	minutos /= 60;
}

Model::Actividad::Actividad(int idActividad, const char* nombre)
{
	this->idActividad = idActividad;
	this->nombre = (char*)malloc(101);
	strcpy_s(this->nombre, 101, nombre);
	this->segundosTotales = 0;
	this->registrosTotales = 0;
	this->nullFlag = false;

	tablasConjuntos = new std::vector<TextTable>;

	actualizarHorasMinutosSegundos();
}

Model::Actividad::Actividad(int idActividad, const char* nombre, unsigned int segundosTotales)
{
	this->idActividad = idActividad;
	this->nombre = (char*)malloc(101);
	strcpy_s(this->nombre, 101, nombre);
	this->segundosTotales = segundosTotales;
	this->registrosTotales = 0;
	this->nullFlag = false;

	tablasConjuntos = new std::vector<TextTable>;
	listaRegistrosActualizada = false;

	actualizarHorasMinutosSegundos();
}

Model::Actividad::Actividad(int idActividad, const char* nombre, unsigned int segundosTotales, size_t registrosTotales)
{
	this->idActividad = idActividad;
	this->nombre = (char*)malloc(101);
	strcpy_s(this->nombre, 101, nombre);
	this->segundosTotales = segundosTotales;
	this->registrosTotales = registrosTotales;
	this->nullFlag = false;

	tablasConjuntos = new std::vector<TextTable>;
	listaRegistrosActualizada = false;

	actualizarHorasMinutosSegundos();
}

Model::Actividad::Actividad(const Actividad& other)
{
	this->idActividad = other.idActividad;
	this->nombre = (char*)malloc(101);
	strcpy_s(this->nombre, 101, other.nombre);
	this->segundosTotales = other.segundosTotales;
	this->registrosTotales = other.registrosTotales;
	this->nullFlag = false;

	tablasConjuntos = other.tablasConjuntos;
	listaRegistrosActualizada = other.listaRegistrosActualizada;

	actualizarHorasMinutosSegundos();
}

Model::Actividad::Actividad(Actividad&& other) noexcept
{
	this->idActividad = other.idActividad;
	this->nombre = (char*)malloc(101);
	strcpy_s(this->nombre, 101, other.nombre);
	this->segundosTotales = other.segundosTotales;
	this->registrosTotales = other.registrosTotales;
	this->nullFlag = false;

	tablasConjuntos = other.tablasConjuntos;
	listaRegistrosActualizada = other.listaRegistrosActualizada;

	actualizarHorasMinutosSegundos();
}

Model::Actividad::Actividad()
{
	nullFlag = true;
}

Model::Actividad::~Actividad()
{
	delete nombre;
}

Model::Actividad& Model::Actividad::operator=(const Actividad& other)
{
	this->idActividad = other.idActividad;
	this->nombre = (char*)malloc(101);
	strcpy_s(this->nombre, 101, other.nombre);
	this->segundosTotales = other.segundosTotales;
	this->registrosTotales = other.registrosTotales;
	this->nullFlag = false;

	tablasConjuntos = other.tablasConjuntos;
	listaRegistrosActualizada = other.listaRegistrosActualizada;

	actualizarHorasMinutosSegundos();

	return *this;
}

bool Model::Actividad::esActividadNula()
{
	return nullFlag;
}

int Model::Actividad::getIdActividad() const
{
	return idActividad;
}

const char* Model::Actividad::getNombre() const
{
	return nombre;
}

unsigned int Model::Actividad::getSegundosTotales() const
{
	return segundosTotales;
}

const std::vector<Model::ConjuntoRegistros>& Model::Actividad::getConjuntosRegistros()
{
	return conjuntos_registros_filtrados;
}

const std::vector<TextTable>& Model::Actividad::getTablasConjuntos()
{
	return *tablasConjuntos;
}

void Model::Actividad::actualizarTablas()
{
	tablasConjuntos->clear();
	size_t tamConjuntos = conjuntos_registros_filtrados.size();
	for (int i = 0; i < tamConjuntos; i++)
	{
		TextTable tt('-', '|', '+');
		tt.add("ID");
		tt.add("Tiempo consumido");
		tt.add("Fecha de creación");
		tt.add("Descripción");
		tt.endOfRow();
		tt.setAlignment(2, TextTable::Alignment::LEFT);

		const ConjuntoRegistros& cr = conjuntos_registros_filtrados[i];
		const std::vector<Registro>& regs = cr.getConjuntoRegistros();
		for (const Registro& registro : regs)
		{
			tt.add(registro.getIdRegistroString());
			tt.add(registro.getSegundosConsumidosString());
			tt.add(registro.getFechaCreacionString());
			tt.add(registro.getDescripcion());
			tt.endOfRow();
		}
		tablasConjuntos->push_back(tt);
	}
}

size_t Model::Actividad::getRegistrosTotales() const
{
	return registrosTotales;
}

void Model::Actividad::incrementarRegistrosTotales()
{
	registrosTotales++;
}

void Model::Actividad::decrementarRegistrosTotales()
{
	registrosTotales--;
}

void Model::Actividad::reiniciarRegistrosTotales()
{
	registrosTotales = 0;
}

void Model::Actividad::setIdActividad(int idActividad)
{
	this->idActividad = idActividad;
}

void Model::Actividad::setNombre(const char* nombre)
{
	strcpy_s(this->nombre, 101, nombre);
}

void Model::Actividad::setSegundosTotales(unsigned int segundosTotales)
{
	this->segundosTotales = segundosTotales;

	actualizarHorasMinutosSegundos();
}

const char* Model::Actividad::getTiempoConsumido()
{
	char* tiempo = (char*)malloc(60);
	memset(tiempo, 0, 60);

	if (segundosTotales == 0)
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

void Model::Actividad::RegistroModificaTiempo(unsigned int tiempoViejo, unsigned int tiempoNuevo)
{
	GestorConexion* gc = GestorConexion::instanciar();
	sql::ResultSet* res = nullptr;
	sql::PreparedStatement* pstmt = gc->prepareStatement("CALL RegistroModificaTiempo(?,?,?,@m)");
	pstmt->setInt(1, this->idActividad);
	pstmt->setUInt(2, tiempoViejo);
	pstmt->setUInt(3, tiempoNuevo);
	pstmt->execute();

	this->segundosTotales += tiempoNuevo - tiempoViejo;
	actualizarHorasMinutosSegundos();
}

int Model::Actividad::getHoras()
{
	return horas;
}

int Model::Actividad::getMinutos()
{
	return minutos;
}

int Model::Actividad::getSegundos()
{
	return segundos;
}

void Model::Actividad::agregarConjuntoRegistros(const ConjuntoRegistros& cr)
{
	this->conjuntos_registros_filtrados.push_back(cr);
}

void Model::Actividad::limpiarColeccionConjuntos()
{
	this->conjuntos_registros_filtrados.clear();
}

void Model::Actividad::agruparRegistros(int tiempoFiltro)
{
	Model::GestorRegistros* gr = Model::GestorRegistros::instanciar();
	conjuntos_registros_filtrados.clear();
	std::vector<Registro> registros;
	size_t cantidadRegistros = gr->cantidadRegistrosPorActividad(idActividad);
	for (int i = 1, c = 0; c < cantidadRegistros; i++)
	{
		Registro& r = gr->obtenerRegistroPorId(i, idActividad);
		if (r.esRegistroNulo())
			continue;
		c++;
		registros.push_back(r);
	}

	int suma = 0, sRes = 0, x, sAnterior, vecesRepetido;
	std::vector<Registro> conjunto;
	int numeroConjunto = 0;
	size_t tam = registros.size();
	for (int i = 0; i < tam; i++)
	{
		if (suma != 0)
			suma += registros[i].getSegundosConsumidos();
		else
			suma = registros[i].getSegundosConsumidos();

		if (suma < tiempoFiltro)
		{
			conjunto.push_back(registros[i]);
			sRes += registros[i].getSegundosConsumidos();
		}
		else if (suma == tiempoFiltro)
		{
			conjunto.push_back(registros[i]);
			sRes += registros[i].getSegundosConsumidos();
			suma = 0;
			conjuntos_registros_filtrados.push_back(ConjuntoRegistros(++numeroConjunto, conjunto));
			conjunto.clear();
		}
		else if (suma >= 2 * tiempoFiltro)
		{
			if (suma != 0)
			{
				sAnterior = suma - registros[i].getSegundosConsumidos();
				x = abs(tiempoFiltro - sAnterior);
				Registro* resto = new Registro(registros[i]);
				resto->setSegundosConsumidos(x);
				conjunto.push_back(*resto);
				conjuntos_registros_filtrados.push_back(ConjuntoRegistros(++numeroConjunto, conjunto));
				conjunto.clear();
				sRes += x;
				suma -= sAnterior + x;
			}

			vecesRepetido = suma / tiempoFiltro;
			Registro* r = new Registro(registros[i]);
			r->setSegundosConsumidos(tiempoFiltro);
			std::vector<Registro> registroRepetido;
			registroRepetido.push_back(*r);
			for (int j = 0; j < vecesRepetido; j++)
				conjuntos_registros_filtrados.push_back(ConjuntoRegistros(++numeroConjunto, registroRepetido));
			conjunto.clear();

			int resto = suma % tiempoFiltro;
			r->setSegundosConsumidos(resto);
			if (resto != 0)
			{
				conjunto.push_back(*r);
				sRes = 0;
			}
			suma -= vecesRepetido * tiempoFiltro;
		}
		else if (suma > tiempoFiltro)
		{
			x = abs(sRes - tiempoFiltro);
			Registro* r = new Registro(registros[i]);
			r->setSegundosConsumidos(x);
			conjunto.push_back(*r);
			conjuntos_registros_filtrados.push_back(ConjuntoRegistros(++numeroConjunto, conjunto));
			conjunto.clear();
			suma -= tiempoFiltro;
			r->setSegundosConsumidos(suma);
			conjunto.push_back(*r);
			sRes = suma;
		}

		if (sRes == tiempoFiltro)
			sRes = 0;
		else if (sRes > tiempoFiltro)
			sRes -= tiempoFiltro;
	}

	if (!conjunto.empty())
		conjuntos_registros_filtrados.push_back(ConjuntoRegistros(++numeroConjunto, conjunto));
}