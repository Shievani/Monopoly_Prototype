#include "details.h"
#include "monopoly.h"
#include "ui_details.h"

Details::Details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Details)
{
    for (int i = 0; i < numOfCells; i++)
        if (cells[i].type == _City && cells[i].owner > -1)
            cities[cells[i].owner].append(cells[i].name);

    ui->setupUi(this);
    for (int i=0; i<4; i++)
    {
        ui->comboBox->setItemText(i, (players[i].name) + " ("+ QString::number(cities[i].count()) + ")");
    }
    this->on_comboBox_activated(0);
}

Details::~Details()
{
    delete ui;
}


void Details::on_pushButton_clicked()
{
    Details::close();
}

void Details::on_comboBox_activated(int index)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(cities[index]);
}
