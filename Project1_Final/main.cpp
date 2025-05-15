// Libraries
#include "Game.h"
#include <iostream>
using namespace std;

int main() {
    Game game;
    int numPlayers;
    cout << "Enter number of players (2-4): ";
    cin >> numPlayers;
    if (numPlayers < 2 || numPlayers > 4) {
        cout << "Invalid number of players.\n";
        return 1;
    }
    for (int i = 0; i < numPlayers; ++i) {
        string name;
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> name;
        game.addPlayer(name);
    }
    game.start();
    return 0;
}
