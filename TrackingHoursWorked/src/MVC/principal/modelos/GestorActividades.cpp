#include "GestorActividades.h"
#include "GestorDatos.h"
#include "GestorConexion.h"
#include "common.h"
#include <iostream>

Model::GestorActividades* Model::GestorActividades::gestor;
size_t Model::GestorActividades::cantidad_de_filas_en_bd = 0;

Model::GestorActividades::~GestorActividades()
{
    delete gestor;
}

Model::GestorActividades* Model::GestorActividades::instanciar()
{
    if (gestor == nullptr)
        gestor = new Model::GestorActividades();
    return gestor;
}

size_t Model::GestorActividades::cantidadActividades() const
{
    return actividades.size();
}

Model::Actividad& Model::GestorActividades::obtenerActividadPorId(int idActividad)
{
    int index;
    try {
        index = indices.at(idActividad);
    }
    catch (const std::out_of_range e) {
        Actividad* actividadNula = new Actividad();
        return *actividadNula;
    }

    return actividades[index];
}

Model::Actividad& Model::GestorActividades::obtenerActividadPorIndice(int index)
{
    if (index >= cantidadActividades())
    {
        Actividad* actividadNula = new Actividad();
        return *actividadNula;
    }
    return actividades[index];
}

sql::ResultSet* Model::GestorActividades::CrearActividad(const char* nombreActividad)
{
    GestorConexion* gc = GestorConexion::instanciar();
    GestorDatos* gd = GestorDatos::instanciar();
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = gc->prepareStatement("CALL CrearActividad(?,@m)");
    pstmt->setString(1, nombreActividad);
    pstmt->execute();

    pstmt = gc->prepareStatement("SELECT @m");
    res = pstmt->executeQuery();
    res->next();
    sql::SQLString mensaje = res->getString(1);

    if (mensaje == "¡Actividad creada con éxito!")
    {
        int nuevoID = actividades[actividades.size() - 1].getIdActividad() + 1;
        Actividad* actividadNueva = new Actividad(nuevoID, (char*)nombreActividad, 0);
        indices[nuevoID] = (int)cantidadActividades();
        actividades.push_back(*actividadNueva);

        cantidad_de_filas_en_bd++;
        gd->agregar_ActividadEnBD();
        Dame();
    }
    return res;
}

sql::ResultSet* Model::GestorActividades::ModificarActividad(int idActividad, const char* nuevoNombre)
{
    GestorConexion* gc = GestorConexion::instanciar();
    Model::GestorActividades* ga = Model::GestorActividades::instanciar();

    sql::PreparedStatement* pstmt = gc->prepareStatement("CALL ModificarActividad(?,?,@m)");
    pstmt->setInt(1, idActividad);
    pstmt->setString(2, nuevoNombre);
    pstmt->execute();

    pstmt = gc->prepareStatement("SELECT @m");
    sql::ResultSet* res = pstmt->executeQuery();
    res->next();
    sql::SQLString mensaje = res->getString(1);

    if (mensaje == "¡Actividad modificada con éxito!")
    {
        int index = indices.at(idActividad);
        actividades[index].setNombre(nuevoNombre);
    }

    return res;
}

sql::ResultSet* Model::GestorActividades::BorrarActividad(int idActividad)
{
    GestorDatos* gd = GestorDatos::instanciar();
    GestorConexion* gc = GestorConexion::instanciar();
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = gc->prepareStatement("CALL BorrarActividad(?,@m)");
    pstmt->setInt(1, idActividad);

    try {
        pstmt->execute();
    }
    catch (sql::SQLException e) {
        const char* mensaje = e.what();
        std::cout << mensaje << std::endl;
        return nullptr;
    }

    pstmt = gc->prepareStatement("SELECT @m");
    res = pstmt->executeQuery();
    res->next();

    sql::SQLString resultado = res->getString(1).substr(0, 5);
    if (resultado == "ERROR")
        return res;

    cantidad_de_filas_en_bd--;
    gd->eliminar_ActividadEnBD();
    actividades.erase(actividades.begin() + indices[idActividad]);
    indices.clear();
    for (int i = 0; i < actividades.size(); i++)
        indices[actividades[i].getIdActividad()] = i;

    return res;
}

void Model::GestorActividades::Dame()
{
    GestorDatos* gd = GestorDatos::instanciar();
    gd->asignarCantidadActividades(0);

    // Limpio el arreglo
    actividades.clear();

    if (!indices.empty())
        indices.clear();

    GestorConexion* conector = GestorConexion::instanciar();
    sql::Statement* stmt = conector->createStatement();
    sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Actividades");

    int contador = 0;
    while (res->next())
    {
        int idActividad = res->getInt("idActividad");
        sql::SQLString cad = res->getString("nombre");
        const char* nombreActividad = cad.c_str();
        unsigned int segundosTotales = res->getUInt("segundosTotales");

        Actividad* actividadNueva = new Actividad(idActividad, nombreActividad, segundosTotales);

        actividades.push_back(*actividadNueva);
        indices[idActividad] = contador++;

        gd->tomarActividad();
    }
}
