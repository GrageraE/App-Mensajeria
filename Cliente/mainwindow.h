#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cliente.h"
#include "adminhistorial.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void conectado();

    void desconectado(int _razon);

    void mensajeRecibido(QString _mensaje, QString _autor);

    void nombreRepetido();

private slots:
    void on_actionCerrar_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_actionVer_Historial_triggered();

    void on_actionA_adir_Servidor_Actual_triggered();

private:
    Ui::MainWindow *ui;
    Cliente* cliente;
    AdminHistorial* admin;

    const QString CONECTADO = "CONECTADO";
    const QString DESCONECTADO = "DESCONECTADO";
};
#endif // MAINWINDOW_H
