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
    explicit VentanaListaUsuarios(const QList<Usuario>& _listaConectados,
                                  const QList<QString>& _listaBaneados, QWidget *parent = nullptr);
    ~VentanaListaUsuarios();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

signals:
    void expulsar(const Usuario& user, bool ban = false);

private:
    Ui::VentanaListaUsuarios *ui;
    QList<Usuario> listaConectados;
    QList<QString> listaBaneados;
};

#endif // VENTANALISTAUSUARIOS_H
