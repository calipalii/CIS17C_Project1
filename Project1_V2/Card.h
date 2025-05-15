#ifndef CARD_H
#define CARD_H

// Libraries
#include <string>

enum class Color { 
    Red, 
    Green, 
    Blue, 
    Yellow, 
    Wild };
    
enum class Value { 
    Zero, 
    One, 
    Two, 
    Three, 
    Four, 
    Five, 
    Six, 
    Seven, 
    Eight, 
    Nine, 
    Skip, 
    Reverse, 
    DrawTwo, 
    Wild };

class Card {
private:
    Color color;
    Value value;

public:
    Card(Color c, Value v);
    Color getColor() const;
    Value getValue() const;
    std::string toString() const;
    bool canPlayOn(const Card& other) const;
    bool isWild() const;
    bool operator==(const Card& other) const; // for equal
    bool operator<(const Card& other) const;  // for set container
};

#endif
