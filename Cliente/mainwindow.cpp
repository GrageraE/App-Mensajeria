#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cliente.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      cliente(nullptr)
{
    ui->setupUi(this);
    ui->cajaDeMensajes->setReadOnly(true);
    ui->estado->setText(DESCONECTADO);
}

MainWindow::~MainWindow()
{
    if(this->cliente)
    {
        disconnect(this->cliente, &Cliente::mandarConectadoAVentana, this, &MainWindow::conectado);
        disconnect(this->cliente, &Cliente::mandarMensajeRecibidoAVentana, this, &MainWindow::mensajeRecibido);
        disconnect(this->cliente, &Cliente::mandarDesconectadoAVentana, this, &MainWindow::desconectado);
    }
    delete this->cliente;
    delete ui;
}

void MainWindow::on_actionCerrar_triggered()
{
    delete this->cliente;
    exit(0); // 'QWaitCondition: Destroyed while threads are still waiting'
}

void MainWindow::on_pushButton_clicked() // Conectar
{
    QString _url = ui->url->text();
    QString _puerto = ui->puerto->text();
    QString _nombre = ui->nombre->text();
    if(_url.isEmpty() || _puerto.isEmpty() || _nombre.isEmpty())
    {
        QMessageBox::critical(this, "Error", "No se ha especificado puerto, URL o nombre");
        return;
    }
    QRegExp regex("\\d");
    if(regex.exactMatch(_puerto))
    {
        QMessageBox::critical(this, "Error", "El puerto debe de ser un valor numérico");
        return;
    }
    if(this->cliente)
    {
        if(QMessageBox::question(this, "Pregunta", "¿Seguro que desea hacerlo? Se desconectará del servidor actual.")
                == QMessageBox::No)
            return;
        else
            delete this->cliente;
    }
    this->cliente = new Cliente(this, _url, _puerto.toUInt(), _nombre);
    connect(this->cliente, &Cliente::mandarConectadoAVentana, this, &MainWindow::conectado);
    connect(this->cliente, &Cliente::mandarMensajeRecibidoAVentana, this, &MainWindow::mensajeRecibido);
    connect(this->cliente, &Cliente::mandarDesconectadoAVentana, this, &MainWindow::desconectado);
}

void MainWindow::conectado()
{
    ui->estado->setText(CONECTADO);
    ui->cajaDeMensajes->appendPlainText("Te has conectado.");
}

void MainWindow::mensajeRecibido(QString _mensaje)
{
    ui->cajaDeMensajes->appendPlainText(_mensaje);
}

/*!
 * \brief MainWindow::desconectado
 * \note Esta funcion solo se ejecuta cuando se desconecta al cerrar el servidor.
 *       En caso de que se haya desconectado pulsando el boton de desconectar,
 *       no se ejecutara esta funcion y la liberacion de memoria transcurrira en el slot
 *       del boton
 */
void MainWindow::desconectado()
{
    ui->estado->setText(DESCONECTADO);
    ui->cajaDeMensajes->appendPlainText("Te has desconectado.");
    delete this->cliente;
    this->cliente = nullptr;
}

void MainWindow::on_pushButton_2_clicked() // Desconectar
{
    if(this->cliente)
    {
        disconnect(this->cliente, &Cliente::mandarConectadoAVentana, this, &MainWindow::conectado);
        disconnect(this->cliente, &Cliente::mandarMensajeRecibidoAVentana, this, &MainWindow::mensajeRecibido);
        disconnect(this->cliente, &Cliente::mandarDesconectadoAVentana, this, &MainWindow::desconectado);
    }
    delete this->cliente;
    this->cliente = nullptr;
    ui->estado->setText(DESCONECTADO);
    ui->cajaDeMensajes->appendPlainText("Te has desconectado");
}

void MainWindow::on_pushButton_3_clicked() // Enviar mensaje
{
    if(this->cliente)
    {
        QString mensaje = ui->mensaje->text();
        if(!(mensaje.isEmpty()))
        {
            this->cliente->enviarMensaje(mensaje);
            ui->cajaDeMensajes->appendPlainText("Tú: " + mensaje);
        }
        else
            QMessageBox::critical(this, "Error", "El mensaje está vacío");
    }
    else
        QMessageBox::critical(this, "Error", "No te has conectado a ningún servidor");
}
