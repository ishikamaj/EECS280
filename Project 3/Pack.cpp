// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <array>
#include <vector>
#include "Pack.h"
  
using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
// Card cards[24]
// lowest to highest: spades, hearts, clubs, diamonds
// cards[0] = 9 of spades
Pack::Pack() {

    Card NS = {"Nine","Spades"};
    Card TS = {"Ten","Spades"};
    Card JS = {"Jack","Spades"};
    Card QS = {"Queen","Spades"};
    Card KS = {"King","Spades"};
    Card AS = {"Ace","Spades"};

    Card NH = {"Nine","Hearts"};
    Card TH = {"Ten","Hearts"};
    Card JH = {"Jack","Hearts"};
    Card QH = {"Queen","Hearts"};
    Card KH = {"King","Hearts"};
    Card AH = {"Ace","Hearts"};

    Card NC = {"Nine","Clubs"};
    Card TC = {"Ten","Clubs"};
    Card JC = {"Jack","Clubs"};
    Card QC = {"Queen","Clubs"};
    Card KC = {"King","Clubs"};
    Card AC = {"Ace","Clubs"};

    Card ND = {"Nine","Diamonds"};
    Card TD = {"Ten","Diamonds"};
    Card JD = {"Jack","Diamonds"};
    Card QD = {"Queen","Diamonds"};
    Card KD = {"King","Diamonds"};
    Card AD = {"Ace","Diamonds"};

    cards = {NS, TS, JS, QS, KS, AS, NH, TH, JH, QH, KH, AH, 
    NC, TC, JC, QC, KC, AC, ND, TD, JD, QD, KD, AD};

    next = 0;

}   

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
// while (fin >> rank >> of >> suit)
Pack::Pack(std::istream& pack_input) {
    std::string rank;
    std::string of;
    std::string suit;
    int i = 0;
    while(pack_input >> rank >> of >> suit) {
        Card name = {rank, suit};
        cards[i] = name;
        i++;
    } 
    next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments index
// next++
// return arr[next-1]
Card Pack::deal_one() {
    assert(!cards.empty());
    ++next;
 
    return cards[next-1];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    int num = 0;
    while (num < 7) {
        Card first[PACK_SIZE/2];
        Card second[PACK_SIZE/2];
        for (int i = 0; i < PACK_SIZE/2; i++) {
            first[i] = cards[i];
        }
        int index = 0;
        for (int j = PACK_SIZE/2; j < PACK_SIZE; j++) {
            second[index] = cards[j];
            index++;
        }
        int count = 0;
        for (int k = 0; k < PACK_SIZE/2; k++) {
            cards[count] = second[k];
            count++;
            cards[count] = first[k];
            count++;
        }
        num++;
        reset();
    }
}

// EFFECTS: returns true if there are no more cards 
// left in the pack
// arr past arr[23] is empty
bool Pack::empty() const {
    bool isempty = false;
    if (next > 23 || next < 0) {
        isempty = true;
    }

    return isempty;
}