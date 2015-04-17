#ifndef MONOPOLY
#define MONOPOLY
#include <QString>
using namespace std;

enum TypeOfCell {_City , _ChanceCard , _Start , _GoToJail , _Type, _CommunityCard, _Jail
                ,_GoTo, _Tax};

//enum lets you choose only one of the defined values of TypeOfCell. now TypeOfCell is just a data type, like int is.

struct Cell
{
    QString name;
    TypeOfCell type;
    int owner;
    int xCoord;
    int yCoord;
    int rent;
};

struct Player{
    string name;
    int position;
    int balance;
    bool inJail;
    bool inGame;

};

extern Player players[];
extern Cell cells[];
extern int numOfCells;

bool canSell(Player&);
bool sellCell(int);
void initialiseGame();
void payingRent(Player &player, int &notification);
bool goToJail(Player &player, int &notification);
void incomeTaxPayment (Player &player, int &notification);
void chanceCards (Player &player, int &notification);
bool sellOwnedCell (Player &player, int &notification, int turn);

#endif // MONOPOLY
