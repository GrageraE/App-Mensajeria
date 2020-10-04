#include "ventanalistausuarios.h"
#include "ui_ventanalistausuarios.h"
#include "usuario.h"

VentanaListaUsuarios::VentanaListaUsuarios(QList<Usuario> _lista, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaListaUsuarios),
    lista(_lista)
{
    ui->setupUi(this);
    // Agregamos los nombres de los clientes en la tabla ---------
    // Primero configuramos la tabla
    ui->tabla->setColumnCount(1);
    ui->tabla->setHorizontalHeaderLabels({"Nombre"});
    for(const auto& i : this->lista)
    {
        // Insertamos una fila en la tabla
        ui->tabla->insertRow(ui->tabla->rowCount());
        // Agregamos el nombre en la ultima fila de la tabla
        ui->tabla->setItem(ui->tabla->rowCount()-1, 0,
                           new QTableWidgetItem(i._nombre));
    }
}

VentanaListaUsuarios::~VentanaListaUsuarios()
{
    delete ui;
}

void VentanaListaUsuarios::on_pushButton_clicked() // Cerrar
{
    accept();
}
