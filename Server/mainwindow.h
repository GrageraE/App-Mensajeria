#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "servidor.h"

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
    void mensajeRecibido(QString _mensaje);

    void usuarioConectado(QString _usuario);

    void usuarioDesconectado(QString _usuario);
private slots:
    void on_actionCerrar_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Servidor* server;
};
#endif // MAINWINDOW_H
