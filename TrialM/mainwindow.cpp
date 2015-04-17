#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monopoly.h"
#include "details.h"
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
  int step=(rolldice1 + rolldice2);


  ui->dice1->display(rolldice1);
  ui->dice2->display(rolldice2);
  ui->turnlabel->setText(QString::number(turn+1));

  if(players[turn].position>numOfCells-12&&(players[turn].position+step)%numOfCells<12)
    {players[turn].balance+=150;
        ui->passgo->setText("You passed the Go cell. Get 150 bucks");
    }
    else ui->passgo->setText(" ");

  players[turn].position = (players[turn].position + step) % numOfCells; /*player's current position i.e which cell they are in is being changed.
                                                             numOfCells because position should not overflow cells */

  int notification = -1;

  if (canSell(players[turn])) notification = 0;
  if (cansellOwnedCell(players[turn],turn))notification = 12;
  if (canpayfine(players[turn])) notification = 14;
  if (freeparking(players[turn])) notification = 11;


  payingRent(players[turn] ,notification);
  incomeTaxPayment(players[turn], notification);
  chanceCards (players[turn], notification);
  communityCards (players[turn],notification);



  int x = cells[players[turn].position].xCoord;
  int y = cells[players[turn].position].yCoord;

  switch(turn)
    {
     case 0:
         ui->Pointer0->move(x,y); //moving the GUI pointer
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
    { int x = cells[10].xCoord; //Cell number 10 is the jail
      int y = cells[10].yCoord;
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

    switch (notification)
    {
    case 0: //To sell _City
        ui->notification->setText("Do you want to buy " +
                                  cells[players[turn].position].name +
                                  " for " +
                                  QString::number(cells[players[turn].position].rent) +
                                  " bucks?");
        this->setResponseButtonsState(true);
        break;
    case 1: //rent
        ui->notification->setText("You are paying rent for " +
                                  cells[players[turn].position].name +
                                  " of " +
                                  QString::number(cells[players[turn].position].rent) +
                                  " bucks to " + players[cells[players[turn].position].owner].name);
        break;
    case 2: //going to jail
        ui->notification->setText("You landed on Go to jail cell. You are being moved to the jail now.");
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
    case 7: //Community Card
            ui->notification->setText("Community card 1. You are paying 200 bucks towards educational fund");
            break;
    case 8: //Community Card
            ui->notification->setText("Community card 2.You are paying 100 bucks towards universal life insurance");
            break;
    case 9: //Community Card
            ui->notification->setText("Community card 3.You are being refunded income tax worth 100 bucks");
            break;
    case 10: //Community Card
            ui->notification->setText("Community card 4. You are being refunded 200 bucks of luxury tax");
            break;
    case 11: //free parking cell
            ui->notification->setText("You have landed on free parking cell.");
            break;
    case 12: //sell already owned cell
            ui->notification->setText("You landed on a cell you already own. Do you want to sell it?");
            this->setResponseButtonsState(true);
            break;
    case 13: //Game end
            ui->notification->setText("You do not have enough money to remain in the game. You lose.");
            break;
    case 14: //pay fine to get out of jail
            ui->notification->setText("Do you want to pay a fine of 50 bucks to get out of jail cell.");
            this->setResponseButtonsState(true);
            break;

    }

    // This line should run at the end of the function
    // If we're waiting for player to decide whether to buy, wait until the decision to increment turn
    if(!canSell(players[turn])) updateTurn(); //counts whose turn is it. 0,1,2,3 which are player array indices
}

void MainWindow::setResponseButtonsState(bool enabled)
{
    ui->YesButton->setEnabled(enabled);
    ui->NoButton->setEnabled(enabled);
    ui->rollButton->setEnabled(!enabled);
}

void MainWindow::on_YesButton_clicked()
{
    if (canSell(players[this->turn])) {
        if(sellCell(this->turn))
            ui->notification->setText("Congrats! You bought " + cells[players[this->turn].position].name);
        else
            ui->notification->setText("You don't have enough money to buy " + cells[players[this->turn].position].name);
    }

    else if(cansellOwnedCell(players[this->turn], this->turn) && (sellOwnedCell(players[turn],this->turn)))
         ui->notification->setText("Congratulation! You sold your property back to the bank");
    else if(canpayfine(players[this->turn])) {
        if(payfine(this->turn)) {
            ui->notification->setText("You are out of jail and in free parking cell now");
            int x = 40;
            int y = 70;
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
        else if(!payfine(this->turn))
            ui->notification->setText("You do not have enough money to get out of jail");
    }


    switch(this->turn)
    {
    case 0:
        ui->P0_details->setText(QString::number(players[0].balance));
        break;
    case 1:
        ui->P1_details->setText(QString::number(players[1].balance));
        break;
    case 2:
        ui->P2_details->setText(QString::number(players[2].balance));
        break;
    case 3:
        ui->P3_details->setText(QString::number(players[3].balance));
        break;
    }

    setResponseButtonsState(false);
    updateTurn();
}

void MainWindow::on_NoButton_clicked()
{
    if(sellCell(this->turn))
        ui->notification->setText("You chose not to buy " + cells[players[this->turn].position].name);
    else if(payfine(this->turn))
         ui->notification->setText("You chose not to get out of jail.");
    setResponseButtonsState(false);
    updateTurn();
}

void MainWindow::updateTurn() {
    int updatesDone = 0;
    do {
        turn = (turn + 1) % 4;
        updatesDone++;
    } while(!players[turn].inGame && updatesDone < 4);

    if (updatesDone == 4) {
        ui->notification->setText("All players lost!");
        setResponseButtonsState(false);
        ui->rollButton->setEnabled(false);
    }
}

void MainWindow::on_playerDetails_clicked()
{
    Details * details = new Details();
    details->exec();
}

void MainWindow::on_Player1Edit_returnPressed()
{
    players[0].name = ui->Player1Edit->text();
}


void MainWindow::on_Player2Edit_returnPressed()
{
    players[1].name = ui->Player2Edit->text();
}

void MainWindow::on_Player3Edit_returnPressed()
{
    players[2].name = ui->Player3Edit->text();
}


void MainWindow::on_Player4Edit_returnPressed()
{
    players[3].name = ui->Player4Edit->text();
}


