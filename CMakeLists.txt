cmake_minimum_required(VERSION 3.30)
project(BlackJack C)

set(CMAKE_C_STANDARD 11)

add_executable(BlackJack main.c
        Deck.c
        Deck.h
        Card.c
        Card.h
        Game.c
        Game.h)
