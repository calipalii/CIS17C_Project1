#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Player.h"
#include <list>
using namespace std;

class Game {
private:
    list<Player> players; // list for player sequence
    Deck deck;
    bool clockwise;
    int currentPlayerIndex;

public:
    Game();
    void addPlayer(const std::string& name);
    void start();
    void playTurn(Player& player);
    void applyEffect(const Card& effect);
    bool isGameOver() const;
    void reversePlayOrder();
    void sortPlayersByHandSize(); // organizing algorithm
};

#endif
