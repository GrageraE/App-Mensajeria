#include "servidor.h"
#include "mainwindow.h"
#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>

Servidor::Servidor(QObject* _parent, const QString& _nombreServidor, quint16 _puerto)
    : QObject(_parent),
      _nombreServidor(_nombreServidor),
      _puerto(_puerto),
      _parent(_parent)
{
    this->servidor = new QWebSocketServer(this->_nombreServidor, QWebSocketServer::SslMode::NonSecureMode, this);
    // Empezamos a escuchar en el puerto sugerido
    if(this->servidor->listen(QHostAddress::Any, this->_puerto))
    {
        qDebug() <<" Servidor activado en puerto " <<this->_puerto;
        // Conectamos esta señal del servidor para recoger su socket
        connect(this->servidor, &QWebSocketServer::newConnection, this, &Servidor::nuevoDispositivoConectado);
    }
    else
    {
        qDebug() <<" Problema al montar el servidor";
        exit(1);
    }
}

Servidor::~Servidor()
{
    // Cerramos el servidor y dealojamos memoria
    this->servidor->close();
    delete this->servidor;
    this->clientes.clear();
}

void Servidor::nuevoDispositivoConectado()
{
    // Recogemos el socket
    QWebSocket* _dispositivo = this->servidor->nextPendingConnection();
    this->clientes.push_back({_dispositivo, QString()}); // Lo incluimos en la lista de clientes para tenerlo controlado
    // Conectamos las señales
    connect(_dispositivo, &QWebSocket::textMessageReceived, this, &Servidor::mensajeRecibido);
    connect(_dispositivo, &QWebSocket::disconnected, this, &Servidor::usuarioDesconectado);
    // Lanzamos señal para que se entere MainWindow
}

void Servidor::mensajeRecibido(QString _mensaje)
{
    if(_mensaje.endsWith("</DESCONECTAR>"))
    {
        _mensaje = _mensaje.remove("<DESCONECTAR>");
        _mensaje = _mensaje.remove("</DESCONECTAR>");
        _mensaje = _mensaje.remove("<NOMBRE>");
        _mensaje = _mensaje.remove("</NOMBRE>");
        qDebug() <<" Se va a desconectar: " <<_mensaje;
        // Eiminamos desde aqui el dispositivo de la lista porque en el slot dedicado no podemos obtener el nombre.
        //      Como los miembros de la lista son punteros, podemos eliminarlos desde aqui, pues la memoria sigue estando
        //      alojada.
        QWebSocket* _dispositivo = qobject_cast<QWebSocket*>(sender());
        this->clientes.removeAll({_dispositivo, _mensaje});
        emit mandarUsuarioDesconectado(_mensaje);
    }
    else if(_mensaje.endsWith("</CONEXION>"))
    {
        // Recogemos el nombre y actualizamos la lista
        _mensaje = _mensaje.remove("<CONEXION>");
        _mensaje = _mensaje.remove("</CONEXION>");
        _mensaje = _mensaje.remove("<NOMBRE>");
        _mensaje = _mensaje.remove("</NOMBRE>");
        qDebug() <<" Nombre del nuevo dispositivo conectado: " <<_mensaje;
        this->clientes[this->clientes.size()-1]._nombre = _mensaje;
        emit mandarUsuarioConectado(_mensaje);
    }
    else
        emit mandarMensajesAVentana(_mensaje);
}

/*!
 * \brief Servidor::usuarioDesconectado
 * \note Este slot solo ejecuta deleteLater, que dealoja memoria.
 */
void Servidor::usuarioDesconectado()
{
    qDebug() <<" Un dispositivo se ha desconectado";
    QWebSocket* _dispositivo = qobject_cast<QWebSocket*>(sender());
    _dispositivo->deleteLater();
}
