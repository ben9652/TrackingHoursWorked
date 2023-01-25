#include "GestorRegistros.h"
#include "GestorActividades.h"
#include "GestorDatos.h"
#include "GestorConexion.h"
#include <ctype.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

Model::GestorRegistros* Model::GestorRegistros::gestor;
size_t Model::GestorRegistros::cantidad_de_filas_en_bd = 0;

Model::GestorRegistros::~GestorRegistros()
{
    delete gestor;
}

Model::GestorRegistros* Model::GestorRegistros::instanciar()
{
    if (gestor == nullptr)
        gestor = new GestorRegistros();
    return gestor;
}

size_t Model::GestorRegistros::cantidadRegistros()
{
    return registros.size();
}

size_t Model::GestorRegistros::cantidadRegistrosPorActividad(int idActividad)
{
    GestorConexion* gc = GestorConexion::instanciar();
    sql::ResultSet* res;
    sql::PreparedStatement* pstmt = gc->prepareStatement("SELECT COUNT(*) FROM Registros WHERE idActividad = ?");
    pstmt->setInt(1, idActividad);
    res = pstmt->executeQuery();
    res->next();

    delete pstmt;

    return res->getUInt(1);
}

Model::Registro& Model::GestorRegistros::obtenerRegistroPorId(int idRegistro, int idActividad)
{
    int index;
    Registro* registroNulo = new Registro();
    Registro& rNulo = *registroNulo;

    Registro* registroDevuelto = (Registro*)malloc(sizeof(Registro));

    try {
        index = indices.at({ idRegistro, idActividad });
        registroDevuelto = &registros[index];
    }
    catch (const std::out_of_range e) {
        return rNulo;
    }

    return *registroDevuelto;
}

Model::Registro& Model::GestorRegistros::obtenerRegistroPorIndice(int index)
{
    if (index >= cantidadRegistros())
    {
        Registro* registroNulo = new Registro();
        return *registroNulo;
    }
    return registros[index];
}

void Model::GestorRegistros::AgregarRegistro(int idActividad, unsigned int segundosConsumidos, const char* descripcion)
{
    GestorConexion* gc = GestorConexion::instanciar();
    Model::GestorActividades* ga = Model::GestorActividades::instanciar();
    Model::GestorDatos* gd = Model::GestorDatos::instanciar();

    try {
        sql::PreparedStatement* pstmt = gc->prepareStatement("CALL AgregarRegistro(?,?,?,@id)");
        pstmt->setInt(1, idActividad);
        pstmt->setUInt(2, segundosConsumidos);
        pstmt->setString(3, descripcion);
        pstmt->execute();

        delete pstmt;
    }
    catch (sql::SQLException e) {
        const char* msg = e.what();
        std::cout << msg << std::endl;
    }

    time_t tActual;
    tActual = time(&tActual);
    tm* fechaCreacion = (tm*)malloc(sizeof(tm));
    localtime_s(fechaCreacion, &tActual);

    gd->agregar_RegistroEnBD();
    Dame();

    cantidad_de_filas_en_bd++;
}

sql::ResultSet* Model::GestorRegistros::EliminarRegistro(int idRegistro, int idActividad)
{
    GestorConexion* gc = GestorConexion::instanciar();
    Model::GestorDatos* gd = Model::GestorDatos::instanciar();
    sql::ResultSet* res;

    sql::PreparedStatement* pstmt = gc->prepareStatement("CALL EliminarRegistro(?,?,@m)");
    pstmt->setInt(1, idRegistro);
    pstmt->setInt(2, idActividad);
    pstmt->execute();

    pstmt = gc->prepareStatement("SELECT @m");
    res = pstmt->executeQuery();
    res->next();

    delete pstmt;

    sql::SQLString resultado = res->getString(1).substr(0, 5);
    if (resultado == "ERROR")
        return res;

    // Actualizo la lista de registros
    cantidad_de_filas_en_bd--;
    gd->eliminar_RegistroEnBD();
    Dame();

    return res;
}

sql::ResultSet* Model::GestorRegistros::BuscarRegistro(int idRegistro, int idActividad, const char* criterioTiempo, unsigned int segundosConsumidos, const char* criterioFecha, const char* fecha, const char* descripcion)
{
    GestorConexion* gc = GestorConexion::instanciar();
    sql::ResultSet* res;

    sql::PreparedStatement* pstmt = gc->prepareStatement("CALL BuscarRegistro(?,?,?,?,?,?,?)");
    pstmt->setInt(1, idRegistro);
    pstmt->setInt(2, idActividad);
    pstmt->setString(3, criterioTiempo);
    pstmt->setUInt(4, segundosConsumidos);
    pstmt->setString(5, criterioFecha);
    pstmt->setString(6, fecha);
    pstmt->setString(7, descripcion);
    res = pstmt->executeQuery();

    delete pstmt;

    return res;
}

void Model::GestorRegistros::Dame()
{
    Model::GestorDatos* gd = Model::GestorDatos::instanciar();
    gd->asignarCantidadRegistros(0);

    GestorActividades* ga = GestorActividades::instanciar();
    for (int i = 0; i < ga->cantidadActividades(); i++)
    {
        Actividad& a = ga->obtenerActividadPorIndice(i);
        a.reiniciarRegistrosTotales();
        a.setSegundosTotales(0);
        a.listaRegistrosActualizada = true;
    }

    // Limpio el arreglo
    registros.clear();

    if (!indices.empty())
        indices.clear();

    GestorConexion* conector = GestorConexion::instanciar();
    sql::Statement* stmt = conector->createStatement();
    sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Registros");

    int contador = 0;
    while (res->next())
    {
        int idRegistro = res->getInt("idRegistro");

        int idActividad = res->getInt("idActividad");

        unsigned int segundosConsumidos = res->getUInt("segundosConsumidos");

        tm* fechaCreacion = (tm*)malloc(sizeof(tm));
        char* fechaString = (char*)malloc(20);
        char* horaString = (char*)malloc(9);
        strcpy_s(fechaString, 20, res->getString("fechaCreacion").c_str());
        char* next_token;
        char* token_fecha;
        char* token_hora;
        token_fecha = strtok_s(fechaString, " ", &next_token);
        token_hora = strtok_s(NULL, " ", &next_token);

        token_fecha = strtok_s(token_fecha, "-", &next_token);
        fechaCreacion->tm_year = atoi(token_fecha) - 1900;
        token_fecha = strtok_s(NULL, "-", &next_token);
        fechaCreacion->tm_mon = atoi(token_fecha);
        token_fecha = strtok_s(NULL, "-", &next_token);
        fechaCreacion->tm_mday = atoi(token_fecha);

        token_hora = strtok_s(token_hora, ":", &next_token);
        fechaCreacion->tm_hour = atoi(token_hora);
        token_hora = strtok_s(NULL, ":", &next_token);
        fechaCreacion->tm_min = atoi(token_hora);
        token_hora = strtok_s(NULL, ":", &next_token);
        fechaCreacion->tm_sec = atoi(token_hora);

        free(fechaString);
        free(horaString);

        sql::SQLString cad = res->getString("descripcion");
        const char* descripcion = cad.c_str();

        Registro* registroNuevo = new Registro(idRegistro, idActividad, segundosConsumidos, fechaCreacion, descripcion);
        registros.push_back(*registroNuevo);
        indices[{idRegistro, idActividad}] = contador++;

        Actividad& actividadActual = ga->obtenerActividadPorId(idActividad);
        actividadActual.incrementarRegistrosTotales();
        unsigned int tiempoActual = actividadActual.getSegundosTotales();
        actividadActual.setSegundosTotales(tiempoActual + segundosConsumidos);

        gd->tomarRegistro();
    }

    delete stmt;
    delete res;
}
