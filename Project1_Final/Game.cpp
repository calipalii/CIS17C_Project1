#include "Game.h"
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

Game::Game() : clockwise(true), currentPlayerIndex(0) {
}

// adds new players to the game
void Game::addPlayer(const string& name) {
    // constructs new player object with name and appends to players container
    players.emplace_back(name);
}

// sets up the game, control function
void Game::start() {
    // checks if players are in 2-4 range
    if (players.size() < 2 || players.size() > 4) {
        cout << "Game requires 2-4 players.\n";
        return;
    }
    // calls deck.initalize to set up the deck
    deck.initialize();
    // deals 7 cards to each player
    for (auto& player : players) {
        for (int i = 0; i < 7; ++i) {
            player.addCard(deck.drawCard());
        }
    }
    
    // takes one card from drawPile and places it in discardPile
    deck.discard(deck.drawCard());
    
    // while loop - runs until game is over
    while (!isGameOver()) {
        // selects current player by advancing an iterator
        auto it = players.begin();
        advance(it, currentPlayerIndex);
        // calls playTurn for current player
        playTurn(*it);
        // checks pending effects in effectQueue
        if (deck.hasPendingEffects()) {
            applyEffect(deck.dequeueEffect());
        }
        // updates currentPlayerIndex to point to the next player
        currentPlayerIndex = (currentPlayerIndex + (clockwise ? 1 : -1) 
                              + players.size()) % players.size();
    }
}

void Game::playTurn(Player& player) {
    Card topCard = deck.getTopDiscard();
    cout << "\nCurrent top card: " << topCard.toString() << "\n";
    player.displayHand();
    if (!player.hasPlayableCard(topCard)) {
        cout << player.getName() << " draws a card.\n";
        player.addCard(deck.drawCard());
        return;
    }
    cout << player.getName() << ", enter card index to play (0 to draw): ";
    int index;
    cin >> index;
    if (index == 0) {
        player.addCard(deck.drawCard());
        return;
    }
    auto it = player.begin();
    advance(it, index - 1);
    Card card = *it;
    if (player.playCard(card, topCard)) {
        deck.discard(card);
        deck.enqueueEffect(card);
        if (card.isWild()) {
            cout << "Choose color (0=Red, 1=Green, 2=Blue, 3=Yellow): ";
            int colorIdx;
            cin >> colorIdx;
            card = Card(static_cast<Color>(colorIdx), Value::Wild);
            deck.discard(card);
        }
        if (player.getHandSize() == 1 && !player.hasSaidUno()) {
            cout << player.getName() << ", type 'uno' to say Uno ";
            cout << "(or press Enter): ";
            // gets input
            string input;
            // ignores white space
            cin.ignore();
            getline(cin, input);
            // makes sure uno was said
            if (input == "uno" || input == "Uno" || input == "UNO") {
                player.setSaidUno(true);
                cout << player.getName() << " said Uno!\n";
            } else {
                cout << player.getName() << " forgot to say Uno! ";
                cout << "Drawing 2 cards.\n";
                // adds 2 cards to player's deck if uno was not "said"
                player.addCard(deck.drawCard());
                player.addCard(deck.drawCard());
            }
    }
}
    else {
        cout << "Invalid card. Draw a card.\n";
        player.addCard(deck.drawCard());
    }
    // equal algorithm to compare hands
    auto it1 = players.begin(), it2 = std::next(it1);
    if (it2 != players.end() && 
        equal(it1->begin(), it1->end(), it2->begin(), it2->end())) {
        cout << it1->getName() << " and " << it2->getName();
        cout << " have identical hands!\n";
    }
    // mutating algorithm
    if (deck.isDrawPileEmpty()) {
        deck.recycleDiscardPile(); 
    }
}

void Game::applyEffect(const Card& effect) {
    switch (effect.getValue()) {
        case Value::Skip:
            currentPlayerIndex = (currentPlayerIndex + (clockwise ? 1 : -1) 
                                  + players.size()) % players.size();
            std::cout << "Next player is skipped.\n";
            break;
        case Value::Reverse:
            reversePlayOrder();
            cout << "Play order reversed.\n";
            break;
        case Value::DrawTwo: {
            auto it = players.begin();
            advance(it, (currentPlayerIndex + (clockwise ? 1 : -1) 
                         + players.size()) % players.size());
            it->addCard(deck.drawCard());
            it->addCard(deck.drawCard());
            cout << it->getName() << " draws two cards.\n";
            break;
        }
        default:
            break;
    }
}

bool Game::isGameOver() const {
    for (const auto& player : players) {
        if (player.getHandSize() == 0) {
            cout << player.getName() << " wins!\n";
            return true;
        }
    }
    return false;
}

void Game::reversePlayOrder() {
    clockwise = !clockwise;
    players.reverse(); // organizing algorithm
}

void Game::sortPlayersByHandSize() {
    players.sort([](const Player& a, const Player& b) {
        return a.getHandSize() < b.getHandSize();
    });
}
