//
// Created by zenta on 26/11/2024.
//

#include "Card.h"
#include <stdio.h>
#include <stdlib.h>

char* cardValueToString(int cardValue) {
    switch (cardValue) {
        case 1:  return "AS";
        case 2:  return "DEUX";
        case 3:  return "TROIS";
        case 4:  return "QUATRE";
        case 5:  return "CINQ";
        case 6:  return "SIX";
        case 7:  return "SEPT";
        case 8:  return "HUIT";
        case 9:  return "NEUF";
        case 10: return "DIX";
        case 11: return "VALET";
        case 12: return "DAME";
        case 13: return "ROI";
        default: return "INCONUS";
    }
}

char* cardColorToString(enum CardColor c) {
    switch (c) {
        case SPADES:  return "PIQUE";
        case CLUBS:   return "TREFLE";
        case HEARTS:  return "COEUR";
        case DIAMOND: return "CAREAU";
        default : return "INCONUS";
    }
}

char* cardToString(struct Card card) {
    char* string = malloc(sizeof(char) * 64);
    int size = sprintf(string, "%s de %s", cardValueToString(card.value), cardColorToString(card.color));
    return string;
}