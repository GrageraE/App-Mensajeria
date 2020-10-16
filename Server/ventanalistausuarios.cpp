#include "ventanalistausuarios.h"
#include "ui_ventanalistausuarios.h"
#include "usuario.h"
#include <QWebSocket>

VentanaListaUsuarios::VentanaListaUsuarios(const QList<Usuario>& _listaConectados,
                                           const QList<QHostAddress>& _listaBaneados, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaListaUsuarios),
    listaConectados(_listaConectados),
    listaBaneados(QList<QString>())
{
    ui->setupUi(this);
    this->setWindowTitle("Lista de usuarios");
    for(const auto& i : _listaBaneados)
    {
        this->listaBaneados.push_back(i.toString());
    }
    // PRIMERA PESTAÑA
    ui->listaConectados->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tabWidget->setTabText(0, "Usuarios conectados");
    ui->numeroUsuarios->setText(QString::number(this->listaConectados.size()));
    // Agregamos los nombres de los clientes en la tabla ---------
    for(const auto& i : this->listaConectados)
    {
        ui->listaConectados->addItem(new QListWidgetItem(i._nombre));
    }
    // SEGUNDA PESTAÑA
    ui->listaBaneados->setSelectionMode(QAbstractItemView::MultiSelection);
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
    for(const auto& i : _listaElementos)
    {
        // Obtenemos su socket
        for(const auto& j : this->listaConectados)
        {
            if(j == i->text())
            {
                emit expulsar(j);
                break;
            }
        }
        // Ahora lo eliminamos de la tabla y de la lista
        delete (ui->listaConectados->takeItem(ui->listaConectados->row(i)));
        ui->numeroUsuarios->setText(QString::number(ui->numeroUsuarios->text().toInt() - 1));
    }
}
void VentanaListaUsuarios::on_pushButton_3_clicked() // Banear
{
    auto _listaElementos = ui->listaConectados->selectedItems();
    for(const auto& i : _listaElementos)
    {
        for(const auto& j : this->listaConectados)
        {
            if(j == i->text())
            {
                emit expulsar(j, true);
                break;
            }
        }
        delete (ui->listaConectados->takeItem(ui->listaConectados->row(i)));
        ui->numeroUsuarios->setText(QString::number(ui->numeroUsuarios->text().toInt() - 1));
    }
}

void VentanaListaUsuarios::on_pushButton_4_clicked() // Desbanear
{
    auto _listaElementos = ui->listaBaneados->selectedItems();
    for(const auto& i : _listaElementos)
    {
        for(const auto& j : this->listaBaneados)
        {
            if(j == i->text())
            {
                emit desbanear(QHostAddress(j));
                break;
            }
        }
        delete (ui->listaBaneados->takeItem(ui->listaBaneados->row(i)));
    }
}
