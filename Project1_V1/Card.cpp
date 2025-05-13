#inlclude "Card.h"

Card::Card(Nums NUM, Colors COLOR) : Num(NUM), Colors(COLOR) {
    // meow
}

Card::~Card() {
    // meow
}

Card::Nums Card::GetNum() {
    return Num;
}

Card::Ranks Card::GetRank() {
    return Color;
}

int Card::GetActionCards() {
    // getting values
    if(Num <= NINE)
        return static_cast<int>(Num);
    return 0;
}
