#include "details.h"
#include "ui_details.h"

Details::Details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Details)
{
    ui->comboBox->addItem("Player 1", NULL);
    ui->setupUi(this);
}

Details::~Details()
{
    delete ui;
}


void Details::on_pushButton_clicked()
{
    Details::close();
}
