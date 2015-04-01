#ifndef MONOPOLY
#define MONOPOLY
#include <string>
using namespace std;

enum TypeOfCell {_RailRoad, _City , _Airport , _ChanceCard , _Start , _GoToJail, _Jail , _IncomeTax};

//enum lets you choose only one of the defined values of TypeOfCell. now TypeOfCell is just a data type, like int is.

struct Cell
{
    string name;
    TypeOfCell type;
    int owner;
    int xCoord;
    int yCoord;
    int rent;
};

struct Player
{
    string name;
    int position;
    int balance;
    bool inJail;
};

Player players[];
Cell cells[];

void initialiseGame();
void payingRent(Player &player);

#endif // MONOPOLY
