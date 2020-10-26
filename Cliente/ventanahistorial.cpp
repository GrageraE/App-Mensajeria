#include "ventanahistorial.h"
#include "ui_ventanahistorial.h"

VentanaHistorial::VentanaHistorial(const QList<Servidor>& _lista, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaHistorial),
    _lista(_lista)
{
    ui->setupUi(this);
    this->setWindowTitle("Historial");
    // Configuramos la tabla
    ui->tabla->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tabla->setSelectionBehavior(QAbstractItemView::SelectRows);
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

void VentanaHistorial::on_pushButton_2_clicked() // Conectarse
{
    const auto _nombre = ui->tabla->selectedItems()[0]->text();
    for(const auto& i : this->_lista)
    {
        if(i._username == _nombre)
        {
            qDebug() <<" Servidor: nombre: " <<i._username <<" Dir: " <<i._dir <<" Puerto: " <<i._port;
            emit conectarAServidor(i);
        }
    }
    accept();
}

void VentanaHistorial::on_pushButton_3_clicked() // Eliminar
{
    const auto _nombre = ui->tabla->selectedItems()[0]->text();
    ui->tabla->removeRow(ui->tabla->currentRow());
    for(const auto& i : this->_lista)
    {
        if(i._username == _nombre)
        {
            qDebug() <<" Servidor: nombre: " <<i._username <<" Dir: " <<i._dir <<" Puerto: " <<i._port;
            emit eliminarServidor(i);
            return;
        }
    }
}
