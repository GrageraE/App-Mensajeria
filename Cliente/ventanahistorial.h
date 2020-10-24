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

private slots:
    void on_pushButton_clicked();

private:
    Ui::VentanaHistorial *ui;
    QList<Servidor> _lista;
};

#endif // VENTANAHISTORIAL_H
