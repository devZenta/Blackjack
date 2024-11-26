//
// Created by zenta on 26/11/2024.
//

#ifndef CARD_H
#define CARD_H

enum CardColor {
    SPADES,
    CLUBS,
    HEARTS,
    DIAMOND
};

struct Card {
    int value;
    enum CardColor color;
};

char* cardToString(struct Card card);

#endif //CARD_H
