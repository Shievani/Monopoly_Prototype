#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monopoly.h"
#include <iostream>
using namespace std;

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
{ srand( time( NULL ) ); // the RNG(random number generator)needs a first input which i am giving here by current time.
  rolldice1 = (rand() % 6) + 1;
  rolldice2 = (rand() % 6) + 1;
  int step=(rolldice1 + rolldice2)%6;// this 6 is because abhi tak 6 hi cells define kiye hain na babuwa


  ui->dice1->display(rolldice1);
  ui->dice2->display(rolldice2);
  ui->turnlabel->setText(QString::number(turn+1));

  players[turn].position = (players[turn].position + step)%6; /*player's current position i.e which cell they are in is being changed.
                                                              NAHI CHAMKA "6" because number of cells is 6. and position should not overflow cells */

  int x = cells[players[turn].position].xCoord;
  int y = cells[players[turn].position].yCoord;

  cout << players[turn].position << endl;
  cout << x << " " << y << endl;

  int notification;
  payingRent(players[turn] ,notification);
  incomeTaxPayment(players[turn], notification);
  chanceCards (players[turn], notification);

  switch(turn)
    {
     case 0:
         ui->Pointer0->move(x, y); //moving the GUI pointer
         ui->P0_details->setText(QString::number(players[0].balance));
         break;
     case 1:
         ui->Pointer1->move(x, y);
         ui->P1_details->setText(QString::number(players[1].balance));
         break;
     case 2:
         ui->Pointer2->move(x, y);
         ui->P2_details->setText(QString::number(players[2].balance));
         break;
     case 3:
         ui->Pointer3->move(x, y);
         ui->P3_details->setText(QString::number(players[3].balance));
         break;
    }
 if (goToJail(players[turn], notification))
    { int x = cells[players[turn].position].xCoord;
      int y = cells[players[turn].position].yCoord;
        switch(turn)
         {
          case 0:
              ui->Pointer0->move(x, y); //moving the GUI pointer
              break;
          case 1:
              ui->Pointer1->move(x, y);
              break;
          case 2:
              ui->Pointer2->move(x, y);
              break;
          case 3:
              ui->Pointer3->move(x, y);
              break;
        }
     }

    turn = (turn +1)%4; //counts whose turn is it. 0,1,2,3 which are player array indices

    switch (notification)
    {
        case 2: //going to jail
            ui->notification->setText("You landed on Go to jail cell. You are being moved to the jail now.");
            break;
    case 1: //rent
        ui->notification->setText("You are paying rent of 200 bucks");
        break;
    case 3: //Income tax
        ui->notification->setText("You are paying income tax of 200 bucks");
        break;
    case 4: //Chance card1
            ui->notification->setText("You landed on a chance block. Randomly selected chance card was picked\
                                       accordingly 200 bucks were deducted from your balance");
            break;
    case 5: //Chance card2
            ui->notification->setText("You landed on a chance block. Randomly selected chance card was picked\
                                       accordingly 200 bucks were added to your balance");
            break;
    case 6: //Chance card3
            ui->notification->setText("You landed on a chance block. Randomly selected chance card was picked\
                                       and you were moved to the start cell");
            break;

    }
}



















