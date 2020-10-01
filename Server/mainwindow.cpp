#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "servidor.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      server(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Servidor");
    ui->cajaDeMensajes->setReadOnly(true);
    ui->usuariosConectados->setText("0");
}

MainWindow::~MainWindow()
{
    delete this->server;
    delete ui;
}

void MainWindow::on_actionCerrar_triggered()
{
    exit(0);
}

void MainWindow::on_pushButton_clicked() // Iniciar
{
    QString nombre = ui->nombreServidor->text();
    QString puertoStr = ui->puerto->text();
    if(nombre.isEmpty() || puertoStr.isEmpty())
    {
        QMessageBox::critical(this, "Error", "No se ha especificado nombre o puerto");
        return;
    }
    quint16 puerto = puertoStr.toUInt();
    this->server = new Servidor(this, nombre, puerto);
    connect(this->server, &Servidor::mandarUsuarioConectado, this, &MainWindow::usuarioConectado);
    connect(this->server, &Servidor::mandarMensajesAVentana, this, &MainWindow::mensajeRecibido);
    connect(this->server, &Servidor::mandarUsuarioDesconectado, this, &MainWindow::usuarioDesconectado);
}

void MainWindow::usuarioConectado(QString _usuario)
{
    ui->cajaDeMensajes->appendPlainText("Se ha conectado " + _usuario);
    ui->usuariosConectados->setText(QString::number(ui->usuariosConectados->text().toInt() + 1));
}

void MainWindow::usuarioDesconectado(QString _usuario)
{
    ui->cajaDeMensajes->appendPlainText("Se ha desconectado " + _usuario);
    ui->usuariosConectados->setText(QString::number(ui->usuariosConectados->text().toInt() - 1));
}

void MainWindow::mensajeRecibido(QString _mensaje, QString _autor)
{
    ui->cajaDeMensajes->appendPlainText(_autor + " > " + _mensaje);
}

void MainWindow::on_pushButton_2_clicked() // Cerrar
{
    ui->usuariosConectados->setText("0");
    delete this->server;
    this->server = nullptr;
}
