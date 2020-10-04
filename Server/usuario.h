#ifndef USUARIO_H
#define USUARIO_H

#include <QString>
#include <QtWebSockets/QWebSocket>

struct Usuario{
    QWebSocket* _conexion;
    QString _nombre;

    bool operator == (const Usuario& _other) const
    {
        return (this->_nombre == _other._nombre);
    }

    bool operator != (const Usuario& _other) const
    {
        return (this->_nombre != _other._nombre);
    }

    bool operator == (const QString& _nombre) const
    {
        return (this->_nombre == _nombre);
    }

    bool operator != (const QString& _nombre) const
    {
        return (this->_nombre != _nombre);
    }
};

#endif // USUARIO_H
