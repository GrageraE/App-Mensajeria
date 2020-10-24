#include "adminhistorial.h"

#include <../third_party/nlohmann/json/single_include/nlohmann/json.hpp>
#include <iomanip> // std::setw
#include <QFile>
#include <fstream>

AdminHistorial::AdminHistorial(QObject* ptr) :
    QObject(ptr), // ptr = NULL
    lista(QList<Servidor>())
{
    QFile _info("./history.json");
    if(_info.exists())
    {
        nlohmann::json j;
        std::ifstream file;
        file.open("./history.json", std::ios::in);
        if(file.fail())
        {
            qDebug() <<"Fallo al abrir el archivo; el archivo existe";
            return;
        }
        file >> j;
        file.close();
        // Interpretamos el JSON
        for(const auto& i : j)
        {
            Servidor s(QString::fromStdString(i[USERNAME].get<std::string>()),
                       QHostAddress(QString::fromStdString(i[DIR].get<std::string>())),
                       i[PORT].get<uint64_t>());
            this->lista.append(s);
        }
    }
    else qDebug() <<"No existe el archivo";
}

AdminHistorial::~AdminHistorial()
{
    // Crafteamos el JSON
    nlohmann::json j;
    int c = 0;
    for(const auto& i : this->lista)
    {
        j.push_back(nlohmann::json::object({{USERNAME, i._username.toStdString()}, {DIR, i._dir.toString().toStdString()},
                                            {PORT, i._port}}));
        ++c;
    }
    // Guardamos el JSON
    std::ofstream file;
    file.open("./history.json", std::ios::out);
    if(file.fail())
    {
        qDebug() <<"Problema al abrir el archivo para guardarlo";
        return;
    }
    file << std::setw(4) << j << std::endl;
    file.close();
}

void AdminHistorial::addServer(const Servidor &s)
{
    this->lista.append(s);
}

void AdminHistorial::removeServer(const Servidor &s)
{
    this->lista.removeAll(s);
}

bool AdminHistorial::checkServer(const Servidor &s)
{
    for(const auto& i : this->lista)
    {
        if(i == s) return true;
    }
    return false;
}
