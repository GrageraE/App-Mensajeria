#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cliente.h"

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

    void desconectado();

    void mensajeRecibido(QString _mensaje);

private slots:
    void on_actionCerrar_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Cliente* cliente;

    const QString CONECTADO = "CONECTADO";
    const QString DESCONECTADO = "DESCONECTADO";
};
#endif // MAINWINDOW_H
