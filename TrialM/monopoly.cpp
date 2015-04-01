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

    /*
    cells[0].name = "GO";
    cells[0].TypeOfCell = _Go;
    cells[0].xCoord = 560;
    cells[0].yCoord = 560;
    cells[0].rent = 0;
    cells[0].owner = -1;

    cells[1].name = "Mumbai";
    cells[1].TypeOfCell = _City;
    cells[1].xCoord = 40;
    cells[1].yCoord = 560;
    cells[1].rent = 200;
    cells[1].owner = -1;

    cells[2].name = "Indira Gandhi Airport";
    cells[2].TypeOfCell = _Airport;
    cells[2].owner = -1;
    cells[2].xCoord = 40;
    cells[2].yCoord = 40;
    cells[2].rent = 300;
    */

