#ifndef DECK_H
#define DECK_H

// Libraries
#include "Card.h"
#include <list>
#include <stack>
#include <queue>
using namespace std;

// Deck class
class Deck {
private:
    list<Card> drawPile; // draw pile list
    stack<Card> discardPile; // discard pile stack
    queue<Card> effectQueue; // special card effects queue

public:
    Deck();
    void initialize();
    void shuffle();
    Card drawCard();
    void discard(Card card);
    Card getTopDiscard() const;
    bool isDrawPileEmpty() const;
    void recycleDiscardPile();
    void enqueueEffect(const Card& card);
    Card dequeueEffect();
    bool hasPendingEffects() const;
};

#endif
