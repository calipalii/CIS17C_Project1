// Deck.cpp
// Libraries
#include "Deck.h"
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

Deck::Deck() {
    initialize();
}

// initializes the deck with 108 cards, necessary for Uno
void Deck::initialize() {
    // ensures the draw pile is clear of any leftovers
    drawPile.clear();
    
    // empties discardPile (a stack)
    while (!discardPile.empty()) 
        discardPile.pop();
    // empties effectQueue (a queue)
    while (!effectQueue.empty()) 
        effectQueue.pop();
    
    // for loop - loops until each color is filled
    for (int c = 0; c < 4; ++c) {
        Color color = static_cast<Color>(c);
        // for loop - loops until each number is filled
        for (int v = 0; v < 10; ++v) {
            drawPile.emplace_back(color, static_cast<Value>(v));
            // Uno has two cards per non-zero number per color
            if (v != 0) 
                drawPile.emplace_back(color, static_cast<Value>(v));
        }
        // emplace_back is more efficient than push_back
        // constructs an object directly at the end of a container
        // eliminates the need for a temp object
        drawPile.emplace_back(color, Value::Skip);
        drawPile.emplace_back(color, Value::Skip);
        drawPile.emplace_back(color, Value::Reverse);
        drawPile.emplace_back(color, Value::Reverse);
        drawPile.emplace_back(color, Value::DrawTwo);
        drawPile.emplace_back(color, Value::DrawTwo);
    }
    // populates wild cards
    for (int i = 0; i < 4; ++i) {
        drawPile.emplace_back(Color::Wild, Value::Wild);
    }
    // call function - shuffle
    shuffle();
}

// randomizes the deck, simulates shuffling
void Deck::shuffle() {
    // holds copy of the cards from draw pile
    list<Card> temp;
    // copies drawPile to temp
    copy(drawPile.begin(), drawPile.end(), back_inserter(temp));
    // empties drawPile so "shuffled" cards can replace it
    drawPile.clear();
    
    // found this online, the Mersenne Twister algorithm
    // claims that rand() is outdated and mt19937 because "it balances speed
    // and quality" 
    random_device rd;
    mt19937 gen(rd());
    
    // while loop - continues until temp is empty
    while (!temp.empty()) {
        // starts at beginning of temp
        auto it = temp.begin();
        // iterator manipulation
        advance(it, gen() % temp.size());
        // adds card to end of draw pile
        drawPile.push_back(*it);
        // removes card from temp
        temp.erase(it);
    }
}

// provides the top card to a certain player
Card Deck::drawCard() {
    // checks if the draw pile is empty
    if (drawPile.empty()) 
        recycleDiscardPile(); // calls recycleDiscardPile if empty
    // retrieves card at the front of drawPile
    Card card = drawPile.front();
    // makes sure drawn card is no longer part of the draw pile
    drawPile.pop_front(); // stl container op
    // returns a copy of the card that was drawn
    return card;
}

void Deck::discard(Card card) {
    discardPile.push(card);
}

Card Deck::getTopDiscard() const {
    return discardPile.top();
}

bool Deck::isDrawPileEmpty() const {
    return drawPile.empty();
}

// when draw pile runs out, discard pile is reused
void Deck::recycleDiscardPile() {
    while (!discardPile.empty()) {
        drawPile.push_back(discardPile.top());
        discardPile.pop();
    }
    shuffle();
}

// action cards get sent to the queue
void Deck::enqueueEffect(const Card& card) {
    // check to see if the card is an action card
    if (card.getValue() == Value::Skip || card.getValue() == Value::Reverse 
        || card.getValue() == Value::DrawTwo) {
        // adds action card to the back of effectQueue
        effectQueue.push(card);
    }
}

// retrieves and removes the next card from effectQueue
Card Deck::dequeueEffect() {
    // checks if effectQueue is empty
    if (effectQueue.empty()) 
        return Card(Color::Wild, Value::Wild);
    // queue = FIFO, front() accesses card that was enqueued earliest
    Card card = effectQueue.front();
    // removes front card
    effectQueue.pop();
    return card;
}

bool Deck::hasPendingEffects() const {
    return !effectQueue.empty();
}
