#pragma once
// header file for cardlib
// RJM 21/01/22


#include <string>

enum Suit { hearts, clubs, diamonds, spades };      // define suits

struct aCard {                          // defines a card
    int cardVal;                        // number 1..13
    Suit cardSuit;                      // suit
};

aCard getCard(std::string stdno);        // declares function to get a card from stdno string
