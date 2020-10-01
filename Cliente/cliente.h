#ifndef CLIENTE_H
#define CLIENTE_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

class Cliente : public QObject
{
    Q_OBJECT
public:
    Cliente(QObject* parent, const QString& _url, quint16 _puerto, const QString& _nombre);

    ~Cliente();

    void enviarMensaje(const QString& _mensaje);

public slots:
    void conectado();

    void mensajeRecibido(QString _mensaje);

    void errorRecibido(QAbstractSocket::SocketError e);
signals:
    void mandarConectadoAVentana();

    void mandarDesconectadoAVentana();

    void mandarMensajeRecibidoAVentana(QString mensaje, QString autor);
private:
    void desconectar();

    QWebSocket* _conexion;
    QString _url;
    quint16 _puerto;
    QString _nombre;
    QObject* _parent;
    bool conectado_b;
};

#endif // CLIENTE_H
