#include "details.h"
#include "monopoly.h"
#include "ui_details.h"

Details::Details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Details)
{
    ui->setupUi(this);
    for (int i=0; i<4; i++)
    {
        ui->comboBox->setItemText(i, QString::fromStdString(players[i].name) );
    }
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
    for (int i=0; i<numOfCells; i++){
        if (cells[i].type == _City && cells[i].owner ==index)
            ui->listWidget->addItem(cells[i].name);
    }
}

