//
// Created by zenta on 25/11/2024.
//

#include "Deck.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct DeckElement* GetElementAt(struct Deck* deck, int index) {
    if(index < 0 || index >= getNbCardInDeck(deck)) {
        return NULL;
    }
    struct DeckElement* temp = deck->first;
    for(int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp;
}

struct Deck * createDeck() {
    struct Deck * deck = malloc(sizeof(struct Deck));
    deck->first = NULL;
    return deck;
}

void freeDeck(struct Deck *deck) {
    while(getNbCardInDeck(deck) > 0) {
        removeCardFromDeck(deck, 0);
    }
    free(deck);
}

void printDeck(struct Deck *deck) {
    struct Card* c= malloc(sizeof(struct Card));
    for(int i = 0; i < getNbCardInDeck(deck); i++) {
        if(getCardFromDeck(deck, i, c)) {
            char * s = cardToString(*c);
            printf("%s\n", s);
            free(s);
        }
    }
    free(c);
}

bool addCardToDeck(struct Deck *deck, struct Card card) {
    if(deck == NULL) {
        return false;
    }
    struct DeckElement * newElement = malloc(sizeof(struct DeckElement));
    newElement->card = card;
    newElement->next = NULL;
    if(deck->first == NULL) {
        deck->first = newElement;
        return true;
    }
    struct DeckElement * current = deck->first;
    while(current->next != NULL) {
        current = current->next;
    }
    current->next = newElement;
    return true;
}

bool removeCardFromDeck(struct Deck *deck, int index) {
    if(index < 0 || index > getNbCardInDeck(deck)-1 || deck->first == NULL) {
        return false;
    }
    struct DeckElement* prev = GetElementAt(deck, index-1);
    struct DeckElement* temp = GetElementAt(deck, index);
    if(prev == NULL) {
        deck->first = temp->next;
        free(temp);
        return true;
    }
    prev->next = temp->next;
    free(temp);
    return true;
}

bool getCardFromDeck(struct Deck *deck, int index, struct Card *card) {
    if(index < 0 || index > getNbCardInDeck(deck)-1 || deck->first == NULL) {
        return false;
    }
    *card = GetElementAt(deck, index)->card;
    return true;
}

int getNbCardInDeck(struct Deck *deck) {
    int count = 0;
    struct DeckElement* temp = deck->first;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

bool popCardFromDeck(struct Deck *deck, int index, struct Card *card) {
    if(index < 0 || index > getNbCardInDeck(deck)-1 || deck->first == NULL) {
        return false;
    }
    if(getCardFromDeck(deck, index, card)) {
        return removeCardFromDeck(deck, index);
    }
    return false;
}

bool shuffleDeck(struct Deck* deck) {
    if (deck == NULL) {
        return false;
    }
    srand(time(NULL));
    struct Deck* temp = createDeck();
    struct Card card;
    while(getNbCardInDeck(deck) > 0) {
        popCardFromDeck(deck, rand() % getNbCardInDeck(deck), &card);
        addCardToDeck(temp, card);
    }
    deck->first = GetElementAt(temp, 0);
    free(temp);

    return true;
}

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