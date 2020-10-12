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
    explicit VentanaListaUsuarios(const QList<Usuario>& _lista, QWidget *parent = nullptr);
    ~VentanaListaUsuarios();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void expulsar(const Usuario& user);

private:
    Ui::VentanaListaUsuarios *ui;
    QList<Usuario> lista;
};

#endif // VENTANALISTAUSUARIOS_H
