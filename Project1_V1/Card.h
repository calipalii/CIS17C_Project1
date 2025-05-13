// Libraries
#include <string>

// Card class
class Card {
public:
    // numbers and action cards
    enum Nums {
        ZERO,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        WILDDRAW4,
        WILD,
        DRAWTWO,
        SKIP,
        REVERSE
    };

    // colors
    enum Colors {
        BLUE,
        GREEN,
        RED,
        YELLOW
    };

    Card(Nums NUM, Colors COLOR)
    virtual ~Card();

    int GetNum();
    int GetColor();

    virtual int GetActionCards();

private:
    Nums Num;
    Colors Color;
};
