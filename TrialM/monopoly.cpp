#include "monopoly.h"
#include <iostream>
#include <ctime> //includes time from computer


Player players[4];
Cell cells[] =
{
    {"Go",_Start,-1,560,560,0}, // {name, TypeOfCell,owner,xCoord,yCoord,rent}; here, each line is a element of array cells[].counting frm 0
    {"Mediteranean Avenue", _City,-1,490,570,60},
    {"Community Chest",_CommunityCard,-1,440,540,0},
    {"Baltic Avenue",_City,-1,390,570,60},
    {"Income Tax",_Tax,-1,340,570,200},
    {"Reading Railroad",_City,-1,290,540,200},
    {"Oriental Avenue",_City,-1,240,570,100},
    {"Chance",_ChanceCard,-1,190,540,0},
    {"Vermont Avenue",_City,-1,140,570,100},
    {"Connecticut Avenue",_City,-1,90,570,120},
    {"Just Visiting",_Type,-1,40,540,0},
    {"St. Charles Place",_City,-1,20,490,140},
    {"Electric Company",_City,-1,20,430,150},
    {"States Avenue",_City,-1,20,390,140},
    {"Virginia Avenue",_City,-1,20,340,160},
    {"Pennsylvania Railroad",_City,-1,20,290,200},
    {"St. James Place",_City,-1,20,240,180},
    {"Community Chest",_CommunityCard,-1,40,180,0},
    {"Tennesse Avenue",_City,-1,20,140,180},
    {"New York Avenue",_City,-1,20,90,200},
    {"Free Parking",_Type,-1,20,50,0},
    {"Kentuckey Avenue",_City,-1,90,20,220},
    {"Chance",_ChanceCard,-1,150,40,0},
    {"Indiana Avenue",_City,-1,190,20,220},
    {"Illinois Avenue",_City,-1,240,20,240},
    {"B & O Railroad",_City,-1,290,20,200},
    {"Atlantic Avenue",_City,-1,340,20,260},
    {"Ventnor Avenue",_City,-1,390,20,260},
    {"Water Works",_City,-1,440,20,150},
    {"Marvin Gardens",_City,-1,490,20,280},
    {"Go to Dungeon",_GoTo,-1,530,10,0},
    {"Pacific Avenue",_City,-1,570,90,300},
    {"North Carolina Avenue",_City,-1,570,140,300},
    {"Community Chest",_CommunityCard,-1,540,190,0},
    {"Pennsylvania Avenue",_City,-1,570,240,320},
    {"Short Line",_City,-1,560,290,0},
    {"Chance", _ChanceCard, -1, 550,340, 0},
    {"Park Place", _City, -1, 570,390,350},
    {"Luxury Tax", _Tax, -1, 545, 440, 400},
    {"BoardWalk Palace", _City, -1, 570, 490,400}
};

int bankReserves= 2000;

void initialiseGame()
{
    for (int i = 0; i < 4; i++)
    {
        players[i].position = 0;
        players[i].inJail = false;
        players[i].balance = 1500;
        players[i].name = ""; //todo
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
        player.balance = player.balance- cells[player.position].rent;
        players[cells[player.position].owner].balance += cells[player.position].rent;
        notification = 1;
     }
}

bool goToJail(Player &player, int &notification)
{
    if (cells[player.position].type == _GoToJail)
        {
            player.position = 4;
            return true;
            notification = 2;
        }
        else return false;
}

void incomeTaxPayment (Player &player, int &notification)
{
    if (cells[player.position].type == _Tax)
        {
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
