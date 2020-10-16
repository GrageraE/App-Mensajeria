#include "servidor.h"
#include "usuario.h"
#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>

Servidor::Servidor(QObject* _parent, const QString& _nombreServidor, quint16 _puerto)
    : QObject(_parent),
      _nombreServidor(_nombreServidor),
      _puerto(_puerto),
      _parent(_parent),
      banadmin(nullptr)
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
    // Cargamos los usuarios baneados
    this->banadmin = new BanAdmin;
}

Servidor::~Servidor()
{
    // Cerramos el servidor y dealojamos memoria
    this->servidor->close();
    delete this->servidor;
    this->clientes.clear();
    delete this->banadmin;
}

void Servidor::nuevoDispositivoConectado()
{
    // Recogemos el socket
    QWebSocket* _dispositivo = this->servidor->nextPendingConnection();
    // Revisamos si esta baneado
    if(this->banadmin->checkDireccion(_dispositivo->peerAddress()))
    {
        // Baneado
        _dispositivo->close();
        _dispositivo->deleteLater();
        return;
    }
    this->clientes.push_back({_dispositivo, QString()}); // Lo incluimos en la lista de clientes para tenerlo controlado
    // Conectamos las señales
    connect(_dispositivo, &QWebSocket::textMessageReceived, this, &Servidor::mensajeRecibido);
    connect(_dispositivo, &QWebSocket::disconnected, this, &Servidor::usuarioDesconectado);
}

void Servidor::mensajeRecibido(QString _mensaje)
{
    if(_mensaje.endsWith(DESCONEXION_END))
    {
        _mensaje = _mensaje.remove(DESCONEXION);
        _mensaje = _mensaje.remove(DESCONEXION_END);
        _mensaje = _mensaje.remove(NOMBRE);
        _mensaje = _mensaje.remove(NOMBRE_END);
        qDebug() <<" Se va a desconectar: " <<_mensaje;
        // Eiminamos desde aqui el dispositivo de la lista porque en el slot dedicado no podemos obtener el nombre.
        //      Como los miembros de la lista son punteros, podemos eliminarlos desde aqui, pues la memoria sigue estando
        //      alojada.
        QWebSocket* _dispositivo = qobject_cast<QWebSocket*>(sender());
        this->clientes.removeAll({_dispositivo, _mensaje});
        // Informamos a los participantes
        for(const auto& i : this->clientes)
        {
            if(i != _mensaje)
                i._conexion->sendTextMessage("Se ha desconectado " + _mensaje);
        }
        emit mandarUsuarioDesconectado(_mensaje);
    }
    else if(_mensaje.endsWith(CONEXION_END))
    {
        // Recogemos el nombre y actualizamos la lista
        _mensaje = _mensaje.remove(CONEXION);
        _mensaje = _mensaje.remove(CONEXION_END);
        _mensaje = _mensaje.remove(NOMBRE);
        _mensaje = _mensaje.remove(NOMBRE_END);
        qDebug() <<" Nombre del nuevo dispositivo conectado: " <<_mensaje;
        // Revidamos si el nombre ya esta en uso
        for(const auto& i : this->clientes)
        {
            if(i == _mensaje)
            {
                // Nombre repetido
                this->clientes[this->clientes.size()-1]._conexion->sendTextMessage("<NOMBRE_REPETIDO>");
                this->clientes.removeAt(this->clientes.size()-1);
                return;
            }
        }
        // Usamos el ultimo elemento porque es el que tendria que contener el socket recien conectado.
        //  Puede que si se conectan dos disp. a la vez se mezclen los nombres
        this->clientes[this->clientes.size()-1]._nombre = _mensaje;
        // Informamos a los participantes
        for(const auto& i : this->clientes)
        {
            if(i != _mensaje)
                i._conexion->sendTextMessage("Se ha conectado " + _mensaje);
        }
        emit mandarUsuarioConectado(_mensaje);
    }
    else
    {
        // La notacion [(<=>)] solo la usamos cuando mandamos varios datos.
        auto datosMensaje = _mensaje.split(SPLITER, Qt::SkipEmptyParts);
        for(const auto& i : this->clientes) // Enviamos los mensajes a todos los usuarios conectados
        {
            if(i != datosMensaje.last())
                i._conexion->sendTextMessage(_mensaje + SPLITER + datosMensaje.last());
        }
        emit mandarMensajesAVentana(datosMensaje.first(), datosMensaje.last());
    }
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

const QList<Usuario>& Servidor::getClientes() const
{
    return this->clientes;
}

const QList<QHostAddress>& Servidor::getBaneados() const
{
    return this->banadmin->getList();
}

/*!
 * \brief Servidor::expulsarCliente. Solo informa al cliente expulsado, entonces él mismo se desconecta.
 * \param _cliente El socket a cerrar
 * \param ban Si hay que banear al usuario. Por defecto: false
 */
void Servidor::expulsarCliente(const Usuario& _cliente, bool ban)
{
    if(ban)
    {
        this->banadmin->addDireccion(_cliente._conexion->peerAddress());
    }
    _cliente._conexion->sendTextMessage(EXPULSADO);
    //i._conexion->close(); <- Para que el cliente no piense que se ha perdido la conexion,
    //                          vamos a dejar que el cliente cierre la conexion
}

void Servidor::desbanear(const QHostAddress& _user)
{
    this->banadmin->removeDireccion(_user);
}
