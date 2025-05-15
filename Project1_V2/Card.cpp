// Card.cpp
// Libraries
#include "Card.h"
using namespace std;

Card::Card(Color c, Value v) : color(c), value(v) {
}

Color Card::getColor() const { 
    return color; 
}

Value Card::getValue() const { 
    return value; 
}

// Idea from github @nliampisan 's "gameuno"
string Card::toString() const {
    string colorStr;
    switch (color) {
        case Color::Red: colorStr = "Red"; break;
        case Color::Green: colorStr = "Green"; break;
        case Color::Blue: colorStr = "Blue"; break;
        case Color::Yellow: colorStr = "Yellow"; break;
        case Color::Wild: colorStr = "Wild"; break;
    }
    string valueStr;
    switch (value) {
        case Value::Zero: valueStr = "0"; break;
        case Value::One: valueStr = "1"; break;
        case Value::Two: valueStr = "2"; break;
        case Value::Three: valueStr = "3"; break;
        case Value::Four: valueStr = "4"; break;
        case Value::Five: valueStr = "5"; break;
        case Value::Six: valueStr = "6"; break;
        case Value::Seven: valueStr = "7"; break;
        case Value::Eight: valueStr = "8"; break;
        case Value::Nine: valueStr = "9"; break;
        case Value::Skip: valueStr = "Skip"; break;
        case Value::Reverse: valueStr = "Reverse"; break;
        case Value::DrawTwo: valueStr = "Draw Two"; break;
        case Value::Wild: valueStr = "Wild"; break;
    }
    return colorStr + " " + valueStr;
}

bool Card::canPlayOn(const Card& other) const {
    return color == other.color || value == other.value || color == Color::Wild;
}

bool Card::isWild() const {
    return color == Color::Wild;
}

bool Card::operator==(const Card& other) const {
    return color == other.color && value == other.value;
}

bool Card::operator<(const Card& other) const {
    if (color != other.color) return static_cast<int>(color)
        < static_cast<int>(other.color);
    return static_cast<int>(value) < static_cast<int>(other.value);
}
