#include "ConjuntoRegistros.h"

Model::ConjuntoRegistros::ConjuntoRegistros(int idConjuntoRegistros, const std::vector<Registro>& registros_agrupados)
{
    this->idConjuntoRegistros = idConjuntoRegistros;
    this->registros_agrupados = registros_agrupados;
}

int Model::ConjuntoRegistros::getIdConjuntoRegistros() const
{
    return idConjuntoRegistros;
}

const std::vector<Model::Registro>& Model::ConjuntoRegistros::getConjuntoRegistros() const
{
    return registros_agrupados;
}

void Model::ConjuntoRegistros::setIdConjuntoRegistros(int idConjuntoRegistros)
{
    this->idConjuntoRegistros = idConjuntoRegistros;
}