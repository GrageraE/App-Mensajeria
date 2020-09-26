#ifndef CLIENTE_H
#define CLIENTE_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class Cliente : public QObject
{
    Q_OBJECT
public:
    Cliente(QObject* parent, QString& _url, quint16 _puerto, QString& _nombre);

    ~Cliente();

    void desconectar();

    void enviarMensaje(QString& _mensaje);

public slots:
    void conectado();

    void desconectado();

    void mensajeRecibido(QString _mensaje);

    void errorRecibido(QAbstractSocket::SocketError e);
signals:
    void mandarConectadoAVentana();

    void mandarDesconectadoAVentana();

    void mandarMensajeRecibidoAVentana(QString _mensaje);
private:
    QWebSocket* _conexion;
    QString _url;
    quint16 _puerto;
    QString _nombre;
    QObject* _parent;
    bool conectado_b;
};

#endif // CLIENTE_H
