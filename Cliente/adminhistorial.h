#ifndef ADMINHISTORIAL_H
#define ADMINHISTORIAL_H

#include <QObject>
#include "serverDef.h"

class AdminHistorial : QObject
{
    Q_OBJECT

    // Constantes para el JSON
    const std::string USERNAME = "Username";
    const std::string DIR = "Dir";
    const std::string PORT = "Port";

public:
    AdminHistorial(QObject* ptr = nullptr);

    ~AdminHistorial();

    const QList<Servidor>& getLista() const
    {
        return this->lista;
    }

    QList<Servidor>& getLista()
    {
        return this->lista;
    }

    void addServer(const Servidor& s);

    void removeServer(const Servidor& s);

    bool checkServer(const Servidor& s);

private:
    QList<Servidor> lista;
};

#endif // ADMINHISTORIAL_H
