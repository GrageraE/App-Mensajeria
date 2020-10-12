#include "ventanalistausuarios.h"
#include "ui_ventanalistausuarios.h"
#include "usuario.h"
#include <QWebSocket>

VentanaListaUsuarios::VentanaListaUsuarios(const QList<Usuario>& _lista, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaListaUsuarios),
    lista(_lista)
{
    ui->setupUi(this);
    this->setWindowTitle("Lista de usuarios");
    ui->numeroUsuarios->setText(QString::number(this->lista.size()));
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

void VentanaListaUsuarios::on_pushButton_2_clicked() // Expulsar
{
    // Obtenemos el nombre seleccionado en la tabla
    auto _listaElementos = ui->tabla->selectedItems();
    if(_listaElementos.size() == 1)
    {
        QString _nombre = _listaElementos[0]->text();
        // Obtenemos su socket
        for(const auto& i : this->lista)
        {
            if(i == _nombre)
            {
                emit expulsar(i);
                break;
            }
        }
        // Ahora los eliminamos de la tabla y de la lista
        ui->tabla->removeRow(ui->tabla->row(_listaElementos[0]));
        ui->numeroUsuarios->setText(QString::number(ui->numeroUsuarios->text().toInt() - 1));
    }
}
void VentanaListaUsuarios::on_pushButton_3_clicked() // Banear
{

}
