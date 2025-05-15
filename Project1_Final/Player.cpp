// Player.cpp
// Libraries
#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(const std::string& n) : name(n), saidUno(false) {
}

string Player::getName() const { 
    return name; 
}

// adds a card to player's hand
void Player::addCard(const Card& card) {
    // inserts card into player's hand (set)
    hand.insert(card);
    // calls updateColorCounts
    updateColorCounts(card, true);
}

// handles card that the player wants to play
bool Player::playCard(const Card& card, const Card& topCard) {
    // hand (sorted associative container), stores iterator result
    // find is logarithmic time O(log n)
    auto it = hand.find(card);
    // makes sure the card was in the hand and that it can be played on the
    // top card
    if (it != hand.end() && card.canPlayOn(topCard)) {
        hand.erase(it); // removes card from hand
        updateColorCounts(card, false); // updates colorCounts map
        saidUno = false; // makes sure uno count is set to false
        return true;
    }
    return false;
}

bool Player::hasCard(const Card& card) const {
    return hand.find(card) != hand.end();
}

bool Player::hasPlayableCard(const Card& topCard) const {
    for (const auto& card : hand) {
        if (card.canPlayOn(topCard)) return true;
    }
    return false;
}

void Player::sayUno() {
    saidUno = true;
}

bool Player::hasSaidUno() const {
    return saidUno;
}

int Player::getHandSize() const {
    return hand.size();
}

// updates colorCounts map
void Player::updateColorCounts(const Card& card, bool add) {
    // checks if card is wild
    if (card.getColor() != Color::Wild) {
        // increments or decrements the count for card's color
        colorCounts[card.getColor()] += add ? 1 : -1;
        // checks if color count is 0
        if (colorCounts[card.getColor()] == 0) {
            // removes color from the map
            colorCounts.erase(card.getColor());
        }
    }
}

// return the number of cards of a specified color in the colorCount's map
int Player::getColorCount(Color color) const {
    // searches for specified color in colorCounts, returns iterator
    auto it = colorCounts.find(color);
    // returns count of cards for the color
    // if color found, returns integer count stored in the map's key-value pair
    return it != colorCounts.end() ? it->second : 0;
}

void Player::displayHand() const {
    cout << name << "'s hand:\n";
    int index = 1;
    for (const auto& card : hand) {
        cout << index++ << ". " << card.toString() << "\n";
    }
}

set<Card>::iterator Player::begin() {
    return hand.begin();
}

set<Card>::iterator Player::end() {
    return hand.end();
}
