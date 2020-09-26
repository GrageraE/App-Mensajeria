#include "cliente.h"
#include <QObject>
#include <QtWebSockets/QWebSocket>

Cliente::Cliente(QObject *parent, QString& _url, quint16 _puerto, QString& _nombre)
    : QObject(parent),
      _conexion(nullptr),
      _url(_url),
      _puerto(_puerto),
      _nombre(_nombre),
      _parent(parent),
      conectado_b(false)
{
    this->_conexion = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this->_parent);
    this->_conexion->open(QUrl("ws://" + this->_url + ":" + QString::number(this->_puerto)));
    qDebug() <<" Conectandose a " <<"ws://" + this->_url + ":" + QString::number(this->_puerto);
    connect(this->_conexion, &QWebSocket::connected, this, &Cliente::conectado);
    connect(this->_conexion, &QWebSocket::disconnected, this, &Cliente::desconectado);
    connect(this->_conexion, &QWebSocket::textMessageReceived, this, &Cliente::mensajeRecibido);
    connect(this->_conexion, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &Cliente::errorRecibido);
}

Cliente::~Cliente()
{
    this->desconectar();
    delete this->_conexion;
}

void Cliente::conectado()
{
    conectado_b = true;
    this->_conexion->sendTextMessage("<CONEXION> <NOMBRE> " + this->_nombre + " </NOMBRE> </CONEXION>");
    emit mandarConectadoAVentana();
}

void Cliente::desconectado()
{
    conectado_b = false;
    emit mandarDesconectadoAVentana();
}

void Cliente::mensajeRecibido(QString _mensaje)
{
    emit mandarMensajeRecibidoAVentana(_mensaje);
}

void Cliente::desconectar()
{
    this->_conexion->sendTextMessage("<DESCONECTAR> <NOMBRE> " + this->_nombre + " </NOMBRE> </DESCONECTAR>");
    this->_conexion->close();
}

void Cliente::enviarMensaje(QString& _mensaje)
{
    this->_conexion->sendTextMessage(_mensaje);
}

void Cliente::errorRecibido(QAbstractSocket::SocketError e)
{
    switch(e)
    {
    case QAbstractSocket::SocketError::ConnectionRefusedError:{
        qDebug() <<" Error: CONNECTION REFUSED ERROR";
    }
        break;
    case QAbstractSocket::SocketError::HostNotFoundError:{
        qDebug() <<" Error: HOST NOT FOUND ERROR";
    }
        break;
    default:{
        qDebug() <<" Ha ocurrido un error";
    }
    }
}
