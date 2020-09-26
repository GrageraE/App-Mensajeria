#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>

class Servidor : public QObject
{
    Q_OBJECT
public:
    Servidor(QObject* _parent, QString _nombreServidor, quint16 _puerto);
    ~Servidor();

    struct Usuario{
        QWebSocket* _conexion;
        QString _nombre;

        bool operator == (const Usuario& _other) const
        {
            return (_nombre == _other._nombre);
        }

        bool operator != (const Usuario& _other) const
        {
            return (_nombre != _other._nombre);
        }
    };

public slots:
    void nuevoDispositivoConectado();

    void usuarioDesconectado();

    void mensajeRecibido(QString _mensaje);
signals:
    void mandarMensajesAVentana(QString _mensaje);

    void mandarUsuarioConectado(QString _nombreUsuario);

    void mandarUsuarioDesconectado(QString _nombreUsuario);
private:
    QWebSocketServer* servidor;
    QList<Usuario> clientes;
    QString _nombreServidor;
    quint16 _puerto;
    QObject* _parent;
};

#endif // SERVIDOR_H
