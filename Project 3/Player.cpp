// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <array>
#include <vector>
#include <cassert>
#include "Player.h"

using namespace std;

class Simple: public Player {
    private:
    const std::string name;
    vector<Card> hand;
    static const int MAX_HAND_SIZE = 5;
    //bool is_dealer;

    public:

    Simple(string name_in) : name(name_in) {}

    //EFFECTS returns player's name
    const std::string & get_name() const override {
        return name;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        assert(!hand.empty());
        Card lowest = hand[0];
        int lowIndex = 0;
        for (size_t i = 0; i < hand.size(); i++) {
            if (Card_less(hand[i], lowest, upcard.get_suit())) {
                lowest = hand[i];
                lowIndex = i;
            }
        }
        hand.erase(hand.begin() + lowIndex);
        hand.push_back(upcard);
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) override {
        assert(!hand.empty());

        Card max_card = hand[0];
        
        vector<int> non_trump_indeces;

       //counts trumps
        int count = 0;
        for(size_t i = 0; i < hand.size(); i++) {
            if(hand[i].is_trump(trump)) {
                ++count;
            }
            else {
                non_trump_indeces.push_back(i);
            }
        }

        //if all trump, sorts, sets max to last card, removes last from vector
        int size = hand.size();
        int maxIndex = 0;
        if(count == size) {
            for(size_t i = 0; i < hand.size(); i++) {
                if (Card_less(max_card, hand[i], trump)) {
                    max_card = hand[i];
                    maxIndex = i;
                }
            }
            //max_card = hand[maxIndex];
            hand.erase(hand.begin() + maxIndex);
        }
        
        else {
            max_card = hand[non_trump_indeces[0]];
            int highestindex = non_trump_indeces[0];
            for(size_t j = 0; j < non_trump_indeces.size(); j++) {
                if(hand[non_trump_indeces[j]] > max_card) {
                    max_card = hand[non_trump_indeces[j]];
                    highestindex = non_trump_indeces[j];
                }
            }
            hand.erase(hand.begin() + highestindex);
        }
        return max_card;
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) override {
        assert(!hand.empty());

        bool matchSuit = false;
        vector <int> matchIndex;
        Card lowest_non_suit;

        //makes vector of indeces where the cards in the hand match led suit
        for (size_t i = 0; i < hand.size(); i++) {
            if (hand[i].get_suit(trump) == led_card.get_suit(trump)) {
                matchSuit = true;
                matchIndex.push_back(i);
            }
        }

        if (matchSuit) {
            Card highest = hand[matchIndex[0]];
            int highIndex = matchIndex[0];

            for (size_t j = 0; j < matchIndex.size(); j++) {
                if (Card_less(highest, hand[matchIndex[j]], 
                    led_card, trump)) {

                    highest = hand[matchIndex[j]];
                    highIndex = matchIndex[j];
                }
            }
            hand.erase(hand.begin() + highIndex);
            return highest;
        }

        else if (!matchSuit) {
            int low_index = 0;
            lowest_non_suit = hand[0];
            for(size_t i = 0; i < hand.size(); i++) {
                if (Card_less(hand[i], lowest_non_suit, trump)) {
                    lowest_non_suit = hand[i];
                    low_index = i;
                }
            }
            hand.erase(hand.begin() + low_index);
            return lowest_non_suit;
        } 
        return lowest_non_suit;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
            
        hand.push_back(c);
    }
    
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit 
    //then return true and change order_up_suit to desired suit.
    //If Player wishes to pass, then do not modify order_up_suit 
    //and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const override{
        int matches = 0;
        if (round == 1) {
            for (int i = 0; i < MAX_HAND_SIZE; i++) {
                if (hand[i].is_face() && 
                    (hand[i].get_suit(order_up_suit) == upcard.get_suit())) {

                    matches++;
                }
            }
            if (matches >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
        }
        else if (round == 2) {
            std::string nextSuit = Suit_next(upcard.get_suit());
            for (int j = 0; j < MAX_HAND_SIZE; j++) {
                if (hand[j].is_face() && (hand[j].get_suit() == nextSuit)) {
                    matches++;
                }
            }
            if (matches >= 1) {
                order_up_suit = nextSuit;
                return true;
            }
            if (is_dealer) {
                order_up_suit = nextSuit;
                return true;
            }
            
        }
        return false; 
    }
};

//////////////////////////////////////////////////////////

class Human: public Player {
    private: 
    const std::string name;
    vector<Card> hand;
    //bool is_dealer;
    static const int MAX_HAND_SIZE = 5;

    public:

    Human(string name_in) : name(name_in) {}

    //EFFECTS returns player's name
    const std::string & get_name() const override {
        return name;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        assert(!hand.empty());
        //prints hand first
        std::sort(hand.begin(), hand.end());
        for (size_t i = 0; i < hand.size(); i++) {
            cout << "Human player " << name << "'s hand: " <<
             "[" << i << "] " << hand[i] << endl;
        }
        
        int index_to_discard;
        
        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << name <<
         ", please select a card to discard:" << endl << endl;
        cin >> index_to_discard;
        if (index_to_discard != -1) {
            hand.push_back(upcard);
            hand.erase(hand.begin() + index_to_discard);
        }
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) override {
        assert(!hand.empty());
        //prints hand first
        std::sort(hand.begin(), hand.end());
        for (size_t i = 0; i < hand.size(); i++) {
            cout << "Human player " << name << "'s hand: " << 
            "[" << i << "] " << hand[i] << endl;
        }
        int choice;
        cout << "Human player " << name <<
         ", please select a card:" << endl;;
        cin >> choice;
        Card play = hand[choice];
        hand.erase(hand.begin() + choice);
        return play;

    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) override {
        assert(!hand.empty());
        //prints hand first
        std::sort(hand.begin(), hand.end());
        for (size_t i = 0; i < hand.size(); i++) {
            cout << "Human player " << name << "'s hand: " <<
             "[" << i << "] " << hand[i] << endl;
        }
        int choice;
        cout << "Human player " << name <<
         ", please select a card:" << endl;
        cin >> choice;
        Card play = hand[choice];
        hand.erase(hand.begin() + choice);
        return play;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }
    
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then 
    //return true and change order_up_suit to desired suit.  
    //If Player wishes to pass, then do not modify order_up_suit 
    //and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const override{
        
        vector<Card> copyhand;
        for(int i = 0; i < MAX_HAND_SIZE; i++) {
            copyhand.push_back(hand[i]);
        }
        std::sort(copyhand.begin(), copyhand.end());
        for(int j = 0; j < MAX_HAND_SIZE; j++) {
            cout << "Human player " << name << "'s hand: " <<
             "[" << j << "] " << copyhand[j] << endl;
        }

        string choice;
        if(round == 1) {
            cout << "Human player " << name <<
             ", please enter a suit, or \"pass\":" << endl;
            cin >> choice;
            if (choice == "pass") {
                return false;
            }
            else {
                order_up_suit = upcard.get_suit();
                return true;
            }
        }
        else if(round == 2) {
            if(!is_dealer) {
                cout << "Human player " << name <<
                 ", please enter a suit, or \"pass\":" << endl;
                cin >> choice;
                order_up_suit = choice;
                return true;
            }
            else if(is_dealer) {
                cout << "Human player " << name <<
                 ", please enter a suit:" << endl;
                cin >> choice;
                order_up_suit = choice;
                return true;
            }
        }
        return false;
    }
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy){
    // We need to check the value of strategy and return 
    // the corresponding player type.
    if (strategy == "Simple") {
        return new Simple(name);
    }
    if (strategy == "Human") {
        return new Human(name);
    }
    
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}

