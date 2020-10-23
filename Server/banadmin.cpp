#include "banadmin.h"
#include <fstream>
#include <QFile> // Para saber si existe el archivo
#include <iomanip> // std::setw
// Submodule
#include <../third_party/nlohmann/json/single_include/nlohmann/json.hpp>

BanAdmin::BanAdmin()
{
    QFile infoArchivo("./config.json");
    if(infoArchivo.exists())
    {
        ifstream lecturaArchivo;
        lecturaArchivo.open("./config.json", std::ios::in);
        if(lecturaArchivo.fail())
        {
            qDebug() <<" Fallo al abrir el archivo";
            return;
        }
        json j;
        lecturaArchivo >> j;
        lecturaArchivo.close();
        qDebug() <<" Archivo leido correctamente";
        // Interpretamos el JSON
        for(const auto& i : j["Banned_IPs"])
        {
            this->listaDirecciones.append(QHostAddress(QString::fromStdString(i)));
        }
    }
    else qDebug() <<" El archivo no existe";
}

BanAdmin::~BanAdmin()
{
    ofstream aperturaArchivo;
    aperturaArchivo.open("./config.json", std::ios::out);
    if(aperturaArchivo.fail())
    {
        qDebug() <<" Fallo al abrir el archivo";
        return;
    }
    // Crafteamos el JSON
    json j;
    // Hay que convertir QHostAddress a std::string:
    auto listaDirecciones_v = this->listaDirecciones.toVector().toStdVector();
    std::vector<std::string> listaDirecciones_str;
    for(const auto& i : listaDirecciones_v)
    {
        listaDirecciones_str.push_back(i.toString().toStdString());
    }
    j["Banned_IPs"] = listaDirecciones_str;
    // Guardamos el JSON en el archivo
    aperturaArchivo << std::setw(4) <<j <<std::endl;
    // Cerramos el archivo y limpiamos
    aperturaArchivo.close();
    this->listaDirecciones.clear();
}

void BanAdmin::addDireccion(const QHostAddress& _dir)
{
    this->listaDirecciones.append(_dir);
}

bool BanAdmin::checkDireccion(const QHostAddress& _dir)
{
    return (this->listaDirecciones.contains(_dir)) ? true : false;
}

void BanAdmin::removeDireccion(const QHostAddress& _dir)
{
    if(this->listaDirecciones.contains(_dir))
        this->listaDirecciones.removeAll(_dir);
}

const QList<QHostAddress>& BanAdmin::getList() const
{
    return this->listaDirecciones;
}
