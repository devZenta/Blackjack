//
// Created by zenta on 29/11/2024.
//

#include "Game.h"
#include "Deck.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int playerAction () {
    int action = 0;
    printf("\nQue voulez-vous faire ? (1: Tirer une carte, 2: Conserver la main) : \n");
    scanf("%d", &action);
    return action;
}

int scoreCheck(struct Card* cards, int numCards) {
    int score = 0;
    int numAces = 0;

    for (int i = 0; i < numCards; i++) {
        if (cards[i].value >= 2 && cards[i].value <= 10) {
            score += cards[i].value;
        } else if (cards[i].value >= 11 && cards[i].value <= 13) {
            score += 10;
        } else if (cards[i].value == 1) {
            numAces++;
            score += 11;
        }
    }

    while (score > 21 && numAces > 0) {
        score -= 10;
        numAces--;
    }

    return score;
}

bool isBust(int score) {
    return score > 21;
}

bool isBlackjack(struct Card* cards, int numCards) {
    return numCards == 2 && scoreCheck(cards, numCards) == 21;
}

bool determineWinner(struct Card* playerCards, int playerNumCards, struct Card* dealerCards, int dealerNumCards) {
    int playerScore = scoreCheck(playerCards, playerNumCards);
    int dealerScore = scoreCheck(dealerCards, dealerNumCards);

    if (isBust(playerScore)) return false;
    if (isBust(dealerScore)) return true;
    return playerScore > dealerScore;
}

int playAgain() {
    int result = 1;

    printf("\n");
    printf("     +---------------------- +  +------------------------+\n");
    printf("     | 0. Quitter le jeu     |  | 1. Relancer une partie |\n");
    printf("     +---------------------- +  +------------------------+\n");
    printf("\n");
    scanf("%d", &result);

    if (result == 0) {
        printf("     +--------------------------------------------------+\n");
        printf("     |            Fin de la partie                      |\n");
        printf("     +--------------------------------------------------+\n");
    }

    return result;
}

void playGame() {
    int play = 1;
    int sys = 0;

    while (play) {
        struct Deck* deck = createDeck();
        for (int i = 0; i < 6; i++) {
            initDeck(deck);
        }
        shuffleDeck(deck);

        struct Card playerCards[10];
        int playerNumCards = 0;

        struct Card dealerCards[10];
        int dealerNumCards = 0;

        for (int i = 0; i < 2; i++) {
            popCardFromDeck(deck, 0, &playerCards[playerNumCards++]);
            popCardFromDeck(deck, 0, &dealerCards[dealerNumCards++]);
        }

        printf("\nVous avez pioche les cartes suivantes :\n");
        for (int i = 0; i < playerNumCards; i++) {
            char* cardStr = cardToString(playerCards[i]);
            printf("%s\n", cardStr);
            free(cardStr);
        }

        printf("\nLe croupier a pioche la carte suivante :\n");
        char* dealerCardStr = cardToString(dealerCards[0]);
        printf("%s\n", dealerCardStr);
        free(dealerCardStr);

        if (isBlackjack(playerCards, playerNumCards)) {
            printf("\nVous avez un Blackjack ! Vous gagnez !\n");
            play = playAgain();
            continue;
        }

        if (isBlackjack(dealerCards, dealerNumCards)) {
            printf("\nLe croupier a un Blackjack ! Vous perdez !\n");
            play = playAgain();
            continue;
        }

        bool playerTurn = true;
        while (playerTurn) {
            int action = playerAction();
            if (action == 1) {
                popCardFromDeck(deck, 0, &playerCards[playerNumCards++]);
                char* cardStr = cardToString(playerCards[playerNumCards - 1]);
                printf("\nVous avez pioche la carte suivante : %s\n", cardStr);
                free(cardStr);

                int playerScore = scoreCheck(playerCards, playerNumCards);
                if (isBust(playerScore)) {
                    printf("\nVous avez depasse 21. Vous perdez !\n");
                    int playerScore = scoreCheck(playerCards, playerNumCards);
                    int dealerScore = scoreCheck(dealerCards, dealerNumCards);
                    printf("\nScore final du joueur : %d\n", playerScore);
                    printf("\nScore final du croupier : %d\n", dealerScore);
                    printf("\nLe croupier a gagne la partie.\n");
                    play = playAgain();
                    playerTurn = false;
                    sys = 1;


                }
            } else {
                playerTurn = false;
            }
        }

        if (!play) continue;


        if (sys == 0) {
            printf("\nC'est au tour du croupier.\n");
            while (scoreCheck(dealerCards, dealerNumCards) < 17) {
                popCardFromDeck(deck, 0, &dealerCards[dealerNumCards++]);
                char* cardStr = cardToString(dealerCards[dealerNumCards - 1]);
                printf("\nLe croupier a pioche la carte suivante : %s\n", cardStr);
                free(cardStr);
            }

            int playerScore = scoreCheck(playerCards, playerNumCards);
            int dealerScore = scoreCheck(dealerCards, dealerNumCards);
            printf("\nScore final du joueur : %d\n", playerScore);
            printf("\nScore final du croupier : %d\n", dealerScore);

            if (determineWinner(playerCards, playerNumCards, dealerCards, dealerNumCards)) {
                printf("\nVous avez gagne la partie !\n");
            } else {
                printf("\nLe croupier a gagne la partie.\n");
            }

            play = playAgain();
        }
    }
}
