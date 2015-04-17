#ifndef MONOPOLY
#define MONOPOLY
#include <QString>
using namespace std;

enum TypeOfCell {_City , _ChanceCard , _Start , _GoToJail , _Type, _CommunityCard, _Jail
                , _Tax};

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
    QString name;
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
bool canpayfine(Player &player);
bool payfine(int turn);
bool freeparking(Player &player);
void initialiseGame();
void payingRent(Player &player, int &notification);
bool goToJail(Player &player, int &notification);
void incomeTaxPayment (Player &player, int &notification);
void chanceCards (Player &player, int &notification);
bool cansellOwnedCell(Player &player , int turn);
bool sellOwnedCell (Player &player,int turn);
void communityCards (Player &player, int &notification);

#endif // MONOPOLY
