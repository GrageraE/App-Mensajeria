#ifndef SERVERDEF_H
#define SERVERDEF_H

#include <QString>
#include <QHostAddress>

struct Servidor
{
    QString _username;
    QHostAddress _dir;
    quint16 _port;

    Servidor(const QString& _un, const QHostAddress& _add, quint16 _p)
        : _username(_un), _dir(_add), _port(_p) {}

    bool operator == (const Servidor& s) const
    {
        if(this->_username == s._username
           && this->_dir == s._dir
           && this->_port == s._port)
            return true;
        return false;
    }

    bool operator != (const Servidor& s) const
    {
        return (*this == s) ? false : true;
    }
};


#endif // SERVERDEF_H
