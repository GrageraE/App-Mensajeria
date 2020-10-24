#include "ventanahistorial.h"
#include "ui_ventanahistorial.h"

VentanaHistorial::VentanaHistorial(const QList<Servidor>& _lista, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaHistorial),
    _lista(_lista)
{
    ui->setupUi(this);
    // Configuramos la tabla
    ui->tabla->setColumnCount(3);
    ui->tabla->setHorizontalHeaderLabels({"Nombre de usuario", "Dirección", "Puerto"});
    // Añadimos los elementos a la tabla
    for(const auto& i : this->_lista)
    {
        ui->tabla->setRowCount(ui->tabla->rowCount() + 1); // Añade una fila
        ui->tabla->setItem(ui->tabla->rowCount() - 1, USERNAME,
                           new QTableWidgetItem(i._username));
        ui->tabla->setItem(ui->tabla->rowCount() - 1, DIR,
                           new QTableWidgetItem(i._dir.toString()));
        ui->tabla->setItem(ui->tabla->rowCount() - 1, PORT,
                           new QTableWidgetItem(QString::number(i._port)));
    }
}

VentanaHistorial::~VentanaHistorial()
{
    delete ui;
}

void VentanaHistorial::on_pushButton_clicked()
{
    reject();
}
