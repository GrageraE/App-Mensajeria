#ifndef VENTANALISTAUSUARIOS_H
#define VENTANALISTAUSUARIOS_H

#include <QDialog>
#include "usuario.h"

namespace Ui {
class VentanaListaUsuarios;
}

class VentanaListaUsuarios : public QDialog
{
    Q_OBJECT

public:
    explicit VentanaListaUsuarios(QList<Usuario> _lista, QWidget *parent = nullptr);
    ~VentanaListaUsuarios();

private slots:
    void on_pushButton_clicked();

private:
    Ui::VentanaListaUsuarios *ui;
    QList<Usuario> lista;
};

#endif // VENTANALISTAUSUARIOS_H
