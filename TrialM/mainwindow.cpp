#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monopoly.h"

Players Player[4];
Cell cells[] =
{
    {"Go",_Start,-1,560,560,0}, // {name, TypeOfCell,owner,xCoord,yCoord,rent};
    {"Mumbai", _City, -1, 40,560,200},
    {"IGA", _Airport,-1,40,40,300},
    {"Chance", _ChanceCard, -1, 560,100, 0},
    {"Jail", _Jail, -1, 560, 300, 0},
    {"Go to Jail", _GoToJail, -1, 560,500,0}
};

void initialiseGame()
{
    for (int i = 0; i < 4; i++)
    {
        Player[i].position = 0;
        Player[i].inJail = false;
        Player[i].balance = 1500;
        Player[i].name = ""; //todo
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialiseGame();
    ui->Pointer0->move(560,560);
    ui->Pointer1->move(560,560);
    ui->Pointer2->move(560,560);
    ui->Pointer3->move(560,560);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rollButton_clicked()
{ rolldice1 = (rand() % 6) + 1;
  rolldice2 = (rand() % 6) + 1;
  turn = (turn + 1)%4; //counts whose turn is it. 0,1,2,3 which are player array indices
  int step=(rolldice1 + rolldice2)%6;// this 6 is because abhi tak 6 hi cells define kiye hain na babuwa


  ui->dice1->display(rolldice1);
  ui->dice2->display(rolldice2);


    switch(turn)
    {
     case 0:
         Player[0].position = Player[0].position + step; //player's current position i.e which cell they are in is being changed.
         ui->Pointer0->move( cells[Player[0].position].xCoord,cells[Player[0].position].yCoord ); //moving the GUI pointer
         break;
     case 1:
         Player[1].position = Player[1].position + step;
         ui->Pointer1->move( cells[Player[1].position].xCoord,cells[Player[1].position].yCoord );
         break;
     case 2:
         Player[2].position = Player[2].position + step;
         ui->Pointer2->move( cells[Player[2].position].xCoord,cells[Player[2].position].yCoord );
         break;
     case 3:
         Player[3].position = Player[3].position + step;
         ui->Pointer3->move( cells[Player[3].position].xCoord,cells[Player[3].position].yCoord );
         break;
    }
}

