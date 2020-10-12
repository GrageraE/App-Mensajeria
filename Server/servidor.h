#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>

#include "usuario.h"
#include "banadmin.h"

class Servidor : public QObject
{
    Q_OBJECT
public:
    Servidor(QObject* _parent, const QString& _nombreServidor, quint16 _puerto);
    ~Servidor();
    const QList<Usuario>& getClientes() const;

public slots:
    void nuevoDispositivoConectado();

    void usuarioDesconectado();

    void mensajeRecibido(QString _mensaje);

    void expulsarCliente(const Usuario& _cliente, bool ban = false);
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
    BanAdmin* banadmin;

    // Constantes para mejorar el parseo
    const QString CONEXION = "<CONEXION> ";
    const QString CONEXION_END = " </CONEXION>";
    const QString DESCONEXION = "<DESCONECTAR> ";
    const QString DESCONEXION_END = " </DESCONECTAR>";
    const QString NOMBRE = "<NOMBRE> ";
    const QString NOMBRE_END = " </NOMBRE>";
    const QString EXPULSADO = "<EXPULSADO>";
    const QString SPLITER = "[(<=>)]";
};

#endif // SERVIDOR_H
