#ifndef PLAYER_H
#define PLAYER_H

// Libraries
#include "Card.h"
#include <set>
#include <map>
#include <string>
using namespace std;

class Player {
private:
    string name;
    set<Card> hand; // set holds unique cards
    map<Color, int> colorCounts; // map tracks card colors
    bool saidUno;

public:
    Player(const std::string& n);
    string getName() const;
    void addCard(const Card& card);
    bool playCard(const Card& card, const Card& topCard);
    bool hasCard(const Card& card) const;
    bool hasPlayableCard(const Card& topCard) const;
    void sayUno();
    bool hasSaidUno() const;
    int getHandSize() const;
    void updateColorCounts(const Card& card, bool add);
    int getColorCount(Color color) const;
    void displayHand() const;
    set<Card>::iterator begin();
    set<Card>::iterator end();
};

#endif
