//
// Created by zenta on 25/11/2024.
//

#ifndef DECK_H
#define DECK_H
#include <stdbool.h>

#include "Card.h"

struct DeckElement {
    struct Card card;
    struct DeckElement * next;
};

struct Deck {
    struct DeckElement * first;
};

struct Deck* createDeck();
void freeDeck(struct Deck * deck);
void printDeck(struct Deck * deck);

bool addCardToDeck(struct Deck* deck, struct Card card);
bool removeCardFromDeck(struct Deck* deck, int index);
bool getCardFromDeck(struct Deck* deck, int index, struct Card * card);
int  getNbCardInDeck(struct Deck* deck);
bool popCardFromDeck(struct Deck* deck, int index, struct Card * card);
bool shuffleDeck(struct Deck *deck);
void createAllCardForColor(struct Deck *deck, enum CardColor color);
void initDeck(struct Deck *deck);

#endif //DECK_H
