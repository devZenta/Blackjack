#include <stdio.h>

#include "Deck.h"
#include "Card.h"

void createAllCardForColor(struct Deck *deck, enum CardColor color) {
    for(int i = 1; i < 14; i++) {
        addCardToDeck(deck, (struct Card){i, color});
    }
}

void initDeck(struct Deck *deck) {
    createAllCardForColor(deck, SPADES);
    createAllCardForColor(deck, CLUBS);
    createAllCardForColor(deck, HEARTS);
    createAllCardForColor(deck, DIAMOND);
}

int main(void)
{
    struct Deck* deck = createDeck();
    initDeck(deck);
    printDeck(deck);

    return 0;
}