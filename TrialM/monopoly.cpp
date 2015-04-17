#include "monopoly.h"
#include <iostream>
#include <ctime> //includes time from computer



Player players[4];
Cell cells[] =
{
    { "Go", _Start, -1, 580, 580, 0 }, // {name, TypeOfCell,owner,xCoord,yCoord,rent}; here, each line is a element of array cells[].counting frm 0
    { "Mediteranean Avenue", _City, -1, 510, 590, 60 },
    { "Community Chest", _CommunityCard, -1, 460, 560, 0 },
    { "Baltic Avenue", _City, -1, 410, 590, 60 },
    { "Income Tax", _Tax, -1, 360, 590, 200 },
    { "Reading Railroad", _City, -1, 310, 560, 200 },
    { "Oriental Avenue", _City, -1, 260, 590, 100 },
    { "Chance", _ChanceCard, -1, 210, 560, 0 },
    { "Vermont Avenue", _City, -1, 160, 590, 100 },
    { "Connecticut Avenue", _City, -1, 110, 590, 120 },
    { "Jail", _Jail, -1, 60, 560, 0 },
    { "St. Charles Place", _City, -1, 40, 510, 140 },
    { "Electric Company", _City, -1, 40, 450, 150 },
    { "States Avenue", _City, -1, 40, 410, 140 },
    { "Virginia Avenue", _City, -1, 40, 360, 160 },
    { "Pennsylvania Railroad", _City, -1, 40, 310, 200 },
    { "St. James Place", _City, -1, 40, 260, 180 },
    { "Community Chest", _CommunityCard, -1, 60, 200, 0 },
    { "Tennesse Avenue", _City, -1, 40, 160, 180 },
    { "New York Avenue", _City, -1, 40, 110, 200 },
    { "Free Parking", _Type, -1, 40, 70, 0 },
    { "Kentuckey Avenue", _City, -1, 110, 40, 220 },
    { "Chance", _ChanceCard, -1, 170, 60, 0 },
    { "Indiana Avenue", _City, -1, 210, 40, 220 },
    { "Illinois Avenue", _City, -1, 260, 40, 240 },
    { "B & O Railroad", _City, -1, 310, 40, 200 },
    { "Atlantic Avenue", _City, -1, 360, 40, 260 },
    { "Ventnor Avenue", _City, -1, 410, 40, 260 },
    { "Water Works", _City, -1, 460, 40, 150 },
    { "Marvin Gardens", _City, -1, 510, 40, 280 },
    { "Go to Dungeon", _GoTo, -1, 550, 30, 0 },
    { "Pacific Avenue", _City, -1, 590, 110, 300 },
    { "North Carolina Avenue", _City, -1, 590, 160, 300 },
    { "Community Chest", _CommunityCard, -1, 560, 210, 0 },
    { "Pennsylvania Avenue", _City, -1, 590, 260, 320 },
    { "Short Line", _City, -1, 580, 310, 0 },
    { "Chance", _ChanceCard, -1, 570, 360, 0 },
    { "Park Place", _City, -1, 590, 410, 350 },
    { "Luxury Tax", _Tax, -1, 565, 460, 400 },
    { "BoardWalk Palace", _City, -1, 590, 510, 400 }
};

int numOfCells = sizeof(cells) / sizeof(cells[0]);

int bankReserves= 2000;

void initialiseGame()
{
    for (int i = 0; i < 4; i++)
    {
        players[i].position = 0;
        players[i].inJail = false;
        players[i].balance = 1500;
        players[i].name = ("Player " + QString::number(i+1)).toStdString();
        players[i].inGame = true;

    }
}

bool canSell (Player &player){
    return (cells[player.position].type == _City && cells[player.position].owner == -1);
}

bool sellCell(int turn)
{
    if (players[turn].balance < cells[players[turn].position].rent) return false;

    cells[players[turn].position].owner = turn;
    players[turn].balance -= cells[players[turn].position].rent;
    return true;
}

void payingRent ( Player &player,int &notification ){      /* this input syntax declares that the input will be an object of stuct Players named anything u want.
                                        pass by reference changes value of input of this function itself. if we pass by value, then players[s}
                                        ki value alag se copy hoti hai and woh change hoti hai. */

    if (cells[player.position].type == _City && cells[player.position].owner != -1) {
        if ( player.balance < cells[player.position].rent)
        {   player.inGame= false;
            notification = 13;
            return;
        }
        player.balance = player.balance- cells[player.position].rent;
        players[cells[player.position].owner].balance += cells[player.position].rent;
        notification = 1;
     }
}

bool goToJail(Player &player, int &notification)
{
    if (cells[player.position].type == _GoToJail)
        {
            player.position = 10 ;
            return true;
            notification = 2;
        }
        else return false;
}

bool cansellOwnedCell(Player &player , int turn){
    if (cells[player.position].type == _City && cells[players[turn].position].owner==turn){
    return true;
}
    else return false;
}

 bool sellOwnedCell (Player &player , int turn){
    if (cells[player.position].type == _City && cells[players[turn].position].owner==turn  ){
        players[turn].balance += cells[players[turn].position].rent;
        return true;
    }
    else return false;
}


void incomeTaxPayment (Player &player, int &notification)
{
    if (cells[player.position].type == _Tax)
        {
        if ( player.balance < 200)
        {   player.inGame= false;
            notification = 13;
            return;
        }
            player.balance=player.balance-200;
            notification = 3;
        }
}

void chanceCards (Player &player, int &notification)
{
    if (cells[player.position].type == _ChanceCard)
       { srand( time( NULL ) );
         int random = rand()%3;
         switch (random)
         {
         case 0 :
            {
             if ( player.balance < 200)
             {   player.inGame= false;
                 notification = 13;
                 return;
             }
             player.balance=player.balance-200; //deducts 200 from account
             notification = 4;
            }
             break;
         case 1 :
            {
             player.balance=player.balance+200; //adds 200 to account
             notification = 5;
            }
             break;
         case 2 :
            {
             player.position = 0; //sends back to start of game
             notification = 6;
            }
             break;
        }

      }

}

void communityCards (Player &player, int &notification)
{
    if (cells[player.position].type == _CommunityCard)
    { srand( time( NULL ) );
        int random = rand()%4;
        switch (random)
        {
        case 0:
            if ( player.balance < 200)
            {   player.inGame= false;
                notification = 13;
                return;
            }
            player.balance=player.balance-200; //deducts 200 from account towards educational fund
            notification = 7;
            break;

        case 1:
            if ( player.balance < 100)
            {   player.inGame= false;
                notification = 13;
                return;
            }
            player.balance=player.balance-100; //deducts 100 from account towards universal life insurance
            notification = 8;
            break;

        case 2:
            player.balance=player.balance+100; //income tax refund
            notification = 9;
            break;

        case 3:
            player.balance=player.balance+200; //luxury tax refund
            notification = 10;
            break;

        }
    }
}

void jail (Player &player, int &notification)
{
    if (cells[player.position].type == _Jail)
    {
        notification = 11;
    }

}
