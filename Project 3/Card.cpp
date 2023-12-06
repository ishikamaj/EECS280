// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

//EFFECTS Initializes Card to the Two of Spades
Card::Card() : Card(RANK_TWO, SUIT_SPADES) {}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in) 
: rank(rank_in), suit(suit_in) {}

//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const {
    //check_valid_suit(suit);
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {

    // if its the left bower, return the suit of the next
    if (is_left_bower(trump)) {
        return trump;
    }
    else { return get_suit();}
    
}

//EFFECTS Returns true if card is a face card 
//(Jack, Queen, King or Ace)
bool Card::is_face() const {
    if (get_rank() == RANK_JACK || get_rank() == RANK_QUEEN || 
    get_rank() == RANK_KING || get_rank() == RANK_ACE) {
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const {
    if (get_suit() == trump) {
        if (get_rank() == RANK_JACK) {
            return true;
        }
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
    if (get_suit() == Suit_next(trump) && get_rank() == RANK_JACK) {
        return true;
    }
    return false;

}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All
// cards of the trump suit are trump cards.  The left 
// bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
    if (get_suit() == trump) {
        return true;
    }
    if (is_left_bower(trump)) {
        return true;
    }
    return false;
}



// NOTE: We HIGHLY recommend you check out the operator
// overloading tutorial in the project spec (see the appendices) 
// before implementing the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    int lhsRank;
    int rhsRank;
    for (int j = 0; j < NUM_RANKS; j++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            lhsRank = j;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            rhsRank = j;
        }
    }

    if (lhsRank != rhsRank) {
        return lhsRank < rhsRank;
    }
    else {
        int lhsSuit;
        int rhsSuit;
        for (int i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lhsSuit = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rhsSuit = i;
            }
        }
        return lhsSuit < rhsSuit;
    }
    return false;
}

//EFFECTS Returns true if lhs is lower value than 
//rhs or the same card as rhs
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {

    if ((lhs < rhs) || (lhs == rhs)) {
        return true;
    }
    return false; 
} 

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {

    int lhsRank;
    int rhsRank;
    for (int j = 0; j < NUM_RANKS; j++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            lhsRank = j;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            rhsRank = j;
        }
    }

    if (lhsRank != rhsRank) {
        return lhsRank > rhsRank;
    }
    else {
        int lhsSuit;
        int rhsSuit;
        for (int i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lhsSuit = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rhsSuit = i;
            }
        }
        return lhsSuit > rhsSuit;
    }
    return false;
}

//EFFECTS Returns true if lhs is higher than rhs or 
//the same card as rhs
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    if ((lhs > rhs) || (lhs == rhs)) {
        return true;
    }
    return false; 
} 

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    int lhsRank;
    int rhsRank;
    for (int j = 0; j < NUM_RANKS; j++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            lhsRank = j;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            rhsRank = j;
        }
    }

    if (lhsRank != rhsRank) {
        return false;
    }
    else {
        int lhsSuit;
        int rhsSuit;
        for (int i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lhsSuit = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rhsSuit = i;
            }
        }
        return lhsSuit == rhsSuit;
    }
    return false; 
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    int lhsRank;
    int rhsRank;
    for (int j = 0; j < NUM_RANKS; j++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            lhsRank = j;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[j]) {
            rhsRank = j;
        }
    }

    if (lhsRank != rhsRank) {
        return true;
    }
    else {
        int lhsSuit;
        int rhsSuit;
        for (int i = 0; i < NUM_SUITS; i++) {
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                lhsSuit = i;
            }
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
                rhsSuit = i;
            }
        }
        return lhsSuit != rhsSuit;
    }
    return false;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
    std::string next_suit = "";
    //check_valid_suit(suit);
    if(suit == "Diamonds") { next_suit = "Hearts"; }
    else if(suit == "Hearts") { next_suit = "Diamonds"; }
    else if(suit == "Clubs") { next_suit = "Spades"; }
    else { next_suit = "Clubs"; }

    return next_suit;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool card_less_helper (const Card &a, const Card &b, const std::string &trump) {
    //Both trump
    if(a.is_trump(trump) && b.is_trump(trump)) {
        if(a.is_right_bower(trump)) { return false;}
        else if(b.is_right_bower(trump)) { return true; }
        else if(a.is_left_bower(trump)) { return false; }
        else if(b.is_left_bower(trump)) { return true; }
        else if (operator<(a,b)) { return true; }
        else {return false;}
    }
    
    //One trump
    else if(a.is_trump(trump) && !b.is_trump(trump)) { return false; }
    else if(!a.is_trump(trump) && b.is_trump(trump)) { return true; }
    else { return false; }

}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b. Uses trump
// to determine order, as described in the spec.
// If both are trump, first check if bowers present
// If both trump but not bowers, then compare ranks
// If only one is trump, that one is higher
// If neither are trump, compare ranks; higher rank is higher
// If ranks are the same, compare suits (this is incorporated in operator<)
bool Card_less(const Card &a, const Card &b, const std::string &trump) {
   
    if(a.is_trump(trump) || b.is_trump(trump)) {
        return card_less_helper(a,b,trump);
    }

    //Neither trump
    else if(operator<(a,b)) { return true; }
    
    else { return false; }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
// Rankings: trump, led suit, others (according to given rankings)
// Both trump? check ranks
// 1 trump? that one is higher
// Both leading? check ranks
// 1 is leading? (other is neither trump or leading) that one is higher
// None of the above? 
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {

    std::string led_suit = led_card.get_suit(trump);

    if(a.is_trump(trump) || b.is_trump(trump)) {
        return card_less_helper(a,b,trump);
    }

    //Both same as leading suit
    else if(a.get_suit(trump) == led_suit && 
    b.get_suit(trump) == led_suit) {
        return Card_less(a,b,trump);
    }
    else if(!(a.get_suit(trump) == led_suit) && 
    b.get_suit(trump) == led_suit) {
        return true;
    }
    else if (a.get_suit(trump) == led_suit && 
    !(b.get_suit(trump) == led_suit)) { 
        return false; 
    }

    //Neither trump nor leading
    else if (operator<(a,b)) { return true; }

    else { return false; }

    
}