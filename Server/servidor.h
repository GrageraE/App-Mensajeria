#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>

class Servidor : public QObject
{
    Q_OBJECT
public:
    Servidor(QObject* _parent, const QString& _nombreServidor, quint16 _puerto);
    ~Servidor();

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

public slots:
    void nuevoDispositivoConectado();

    void usuarioDesconectado();

    void mensajeRecibido(QString _mensaje);
signals:
    void mandarMensajesAVentana(QString _mensaje, QString autor);

    void mandarUsuarioConectado(QString _nombreUsuario);

    void mandarUsuarioDesconectado(QString _nombreUsuario);
private:
    QWebSocketServer* servidor;
    QList<Usuario> clientes;
    QString _nombreServidor;
    quint16 _puerto;
    QObject* _parent;

    // Constantes para mejorar el perseo
    const QString CONEXION = "<CONEXION> ";
    const QString CONEXION_END = " </CONEXION>";
    const QString DESCONEXION = "<DESCONECTAR> ";
    const QString DESCONEXION_END = " </DESCONECTAR>";
    const QString NOMBRE = "<NOMBRE> ";
    const QString NOMBRE_END = " </NOMBRE>";
};

#endif // SERVIDOR_H
