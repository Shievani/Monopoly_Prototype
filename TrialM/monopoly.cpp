#include "monopoly.h"
#include <iostream>
#include <ctime> //includes time from computer


Player players[4];
Cell cells[] =
    {
        {"Go",_Start,-1,560,560,0}, // {name, TypeOfCell,owner,xCoord,yCoord,rent}; here, each line is a element of array cells[].counting frm 0
        {"Mumbai", _City, -1, 40,560,200},
        {"IGA", _City,-1,40,40,300},
        {"Chance", _ChanceCard, -1, 560,100, 0},
        {"Jail", _Jail, -1, 560, 300, 0},
        {"Go to Jail", _GoToJail, -1, 560,500,0},
        {"Sea Line",_City,-1,560,300,0},
        {"Pennsylvania Avenue",_City,-1,570,252,320},
        {"Community Chest",_CommunityCard,-1,560,202,0},
        {"North Carolina Avenue",_City,-1,570,152,300},
        {"Pacific Avenue",_City,-1,570,107,300},
        {"Go to Dungeon",_GoTo,-1,560,42,0},
        {"Marvin Gardens",_City,-1,495,25,280},
        {"Water Works",_City,-1,447,35,150},
        {"Ventnor Avenue",_City,-1,398,25,260},
        {"Atlantic Avenue",_City,-1,350,25,260},
        {"B & O Railroad",_City,-1,300,35,200},
        {"Illinois Avenue",_City,-1,252,25,240},
        {"Indiana Avenue",_City,-1,203,25,220},
        {"Chance",_ChanceCard,-1,153,35,0},
        {"Kentuckey Avenue",_City,-1,107,25,220},
        {"Free Parking",_Type,-1,32,30,0},
        {"New York Avenue",_City,-1,25,107,200},
        {"Tennesse Avenue",_City,-1,25,154,180},
        {"Community Chest",_CommunityCard,-1,35,202,0},
        {"St. James Place",_City,-1,25,252,180},
        {"Pennsylvania Railroad",_City,-1,35,302,200},
        {"Virginia Avenue",_City,-1,25,352,160},
        {"States Avenue",_City,-1,25,398,140},
        {"Electric Company",_City,-1,35,448,150},
        {"St. Charles Place",_City,-1,25,494,140},
        {"Just Visiting",_Type,-1,30,570,0},
        {"Connecticut Avenue",_City,-1,105,577,120},
        {"Vermont Avenue",_City,-1,155,577,100},
        {"Chance",_ChanceCard,-1,203,567,0},
        {"Oriental Avenue",_City,-1,252,577,100},
        {"Reading Railroad",_City,-1,302,567,200},
        {"Income Tax",_Tax,-1,350,562,0},
        {"Baltic Avenue",_City,-1,397,577,60},
        {"Community Chest",_CommunityCard,-1,445,562,0},
        {"Mediterranian Avenue",_City,-1,493,577,60}
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
    Player player = players[turn];

    if (player.balance < cells[player.position].rent) return false;

    cells[player.position].owner = turn;
    player.balance -= cells[player.position].rent;
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
