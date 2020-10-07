#include "cliente.h"
#include <QObject>
#include <QtWebSockets/QWebSocket>

Cliente::Cliente(QObject *parent, const QString& _url, quint16 _puerto, const QString& _nombre)
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
    connect(this->_conexion, &QWebSocket::textMessageReceived, this, &Cliente::mensajeRecibido);
    connect(this->_conexion, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &Cliente::errorRecibido);
}

Cliente::~Cliente()
{
    if(conectado_b)
        this->desconectar();
    this->_conexion->deleteLater();
}

void Cliente::conectado()
{
    conectado_b = true;
    this->_conexion->sendTextMessage("<CONEXION> <NOMBRE> " + this->_nombre + " </NOMBRE> </CONEXION>");
    emit mandarConectadoAVentana();
}

void Cliente::mensajeRecibido(QString _mensaje)
{
    if(_mensaje == "<EXPULSADO>")
    {
        this->_conexion->close();
        emit mandarDesconectadoAVentana(1);
        return;
    }
    auto datosMensaje = _mensaje.split("[(<=>)]", Qt::SkipEmptyParts);
    emit mandarMensajeRecibidoAVentana(datosMensaje.first(), datosMensaje.last());
}

void Cliente::desconectar()
{
    conectado_b = false;
    this->_conexion->sendTextMessage("<DESCONECTAR> <NOMBRE> " + this->_nombre + " </NOMBRE> </DESCONECTAR>");
    this->_conexion->close();
}

void Cliente::enviarMensaje(const QString& _mensaje)
{
    if(conectado_b)
        this->_conexion->sendTextMessage(_mensaje + "[(<=>)]" + this->_nombre);
}

void Cliente::errorRecibido(QAbstractSocket::SocketError e)
{
    switch(e)
    {
    case QAbstractSocket::SocketError::RemoteHostClosedError:
    {
        conectado_b = false;
        emit mandarDesconectadoAVentana(0);
    }
        break;
    default:
        qDebug() <<" Error: " <<qobject_cast<QWebSocket*>(sender())->errorString();
    }
}
