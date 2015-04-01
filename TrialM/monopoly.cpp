#include "monopoly.h"

Player players[4];
Cell cells[] =
    {
        {"Go",_Start,-1,560,560,0}, // {name, TypeOfCell,owner,xCoord,yCoord,rent};
        {"Mumbai", _City, 0, 40,560,200},
        {"IGA", _Airport,-1,40,40,300},
        {"Chance", _ChanceCard, -1, 560,100, 0},
        {"Jail", _Jail, -1, 560, 300, 0},
        {"Go to Jail", _GoToJail, -1, 560,500,0}
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

void payingRent ( Player &player ){      /* this input syntax declares that the input will be an object of stuct Players named anything u want.
                                        pass by reference changes value of input of this function itself. if we pass by value, then players[s}
                                        ki value alag se copy hoti hai and woh change hoti hai. */

    if (cells[player.position].type == _City && cells[player.position].owner != -1) {
        player.balance = player.balance- cells[player.position].rent;
        players[cells[player.position].owner].balance += cells[player.position].rent;
     }
}
