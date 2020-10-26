#ifndef VENTANAHISTORIAL_H
#define VENTANAHISTORIAL_H

#include <QDialog>
#include <QHostAddress>

#include "serverDef.h"

namespace Ui {
class VentanaHistorial;
}

class VentanaHistorial : public QDialog
{
    Q_OBJECT

    enum{
        USERNAME = 0,
        DIR,
        PORT
    };

public:
    explicit VentanaHistorial(const QList<Servidor>& _lista, QWidget *parent = nullptr);
    ~VentanaHistorial();

signals:
    void conectarAServidor(Servidor s);

    void eliminarServidor(Servidor s);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::VentanaHistorial *ui;
    QList<Servidor> _lista;
};

#endif // VENTANAHISTORIAL_H
