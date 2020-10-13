#include "ventanalistausuarios.h"
#include "ui_ventanalistausuarios.h"
#include "usuario.h"
#include <QWebSocket>

VentanaListaUsuarios::VentanaListaUsuarios(const QList<Usuario>& _listaConectados,
                                           const QList<QString>& _listaBaneados, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaListaUsuarios),
    listaConectados(_listaConectados),
    listaBaneados(_listaBaneados)
{
    ui->setupUi(this);
    this->setWindowTitle("Lista de usuarios");
    // PRIMERA PESTAÑA
    ui->tabWidget->setTabText(0, "Usuarios conectados");
    ui->numeroUsuarios->setText(QString::number(this->listaConectados.size()));
    // Agregamos los nombres de los clientes en la tabla ---------
    for(const auto& i : this->listaConectados)
    {
        ui->listaConectados->addItem(new QListWidgetItem(i._nombre));
    }
    // SEGUNDA PESTAÑA
    ui->tabWidget->setTabText(1, "Usuarios baneados");
    for(const auto& i : this->listaBaneados)
    {
        ui->listaBaneados->addItem(new QListWidgetItem(i));
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
    auto _listaElementos = ui->listaConectados->selectedItems();
    if(_listaElementos.size() == 1)
    {
        // Obtenemos su socket
        for(const auto& i : this->listaConectados)
        {
            if(i == _listaElementos[0]->text())
            {
                emit expulsar(i);
                break;
            }
        }
        // Ahora los eliminamos de la tabla y de la lista
        delete (ui->listaConectados->takeItem(ui->listaConectados->row(_listaElementos[0])));
        ui->numeroUsuarios->setText(QString::number(ui->numeroUsuarios->text().toInt() - 1));
    }
}
void VentanaListaUsuarios::on_pushButton_3_clicked() // Banear
{
    auto _listaElementos = ui->listaConectados->selectedItems();
    if(_listaElementos.size() == 1)
    {
        for(const auto& i : this->listaConectados)
        {
            if(i == _listaElementos[0]->text())
            {
                emit expulsar(i, true);
                break;
            }
        }
        delete (ui->listaConectados->takeItem(ui->listaConectados->row(_listaElementos[0])));
        ui->numeroUsuarios->setText(QString::number(ui->numeroUsuarios->text().toInt() - 1));
    }
}

void VentanaListaUsuarios::on_pushButton_4_clicked() // Desbanear
{
    auto _listaElementos = ui->listaBaneados->selectedItems();
    if(_listaElementos.size() == 1)
    {
        for(const auto& i : this->listaBaneados)
        {
            if(i == _listaElementos[0]->text())
            {
                // TODO
                break;
            }
        }
        delete (ui->listaBaneados->takeItem(ui->listaBaneados->row(_listaElementos[0])));
    }
}
