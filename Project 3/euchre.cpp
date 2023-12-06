// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <array>
#include <vector>
#include "Player.h"
#include "Pack.h"

using namespace std;

const int NUM_PLAYERS = 4;
const int NUM_TRICKS = 5;

class Game {
    private:
    int Hand;
    int dealerIndex;
    int leadPlayer;
    int team1_score;
    int team2_score;
    int team1Tricks;
    int team2Tricks;
    int trump_maker_index;
    bool shuffle;
    int currentPlayer;
    string trump;
    int highestCardPlayer;
    Player * players[NUM_PLAYERS];
    Player * team1[2];
    Player * team2[2];
    Pack pack;
    int max_score;
    Card highestCard;
    Card led_card;
    Card compare_card;

    public:
    //Game constructor
    Game(char *argv[]) {
        Card highestCard("Two","Spades");
        Card led_card("Two","Spades");
        Card compare_card("Two","Spades");
        Hand = 0;
        dealerIndex = 0;
        leadPlayer = 1;
        team1_score = 0;
        team2_score = 0;
        team1Tricks = 0;
        team2Tricks = 0;
        trump_maker_index = 0;
        trump = "Spades";
        currentPlayer = 0;
        highestCardPlayer = 1;

        string shuffle_arg = argv[2];
        
        if(shuffle_arg == "shuffle") {
            shuffle = true;
        }
        else if(shuffle_arg == "noshuffle") {
            shuffle = false;
        }
        
        //PLAYER FACTORY
        for (int i = 0; i < NUM_PLAYERS; i++) {
            string name = argv[i * 2 + NUM_PLAYERS];
            string type = argv[i * 2 + NUM_PLAYERS + 1];
            players[i] = Player_factory(name,type);
        }
        team1[0] = players[0];
        team1[1] = players[2];
        team2[0] = players[1];
        team2[1] = players[3];

        //Sets max score to user input value
        max_score = atoi(argv[3]);

        char* inName = argv[1];
        ifstream fin(inName);
        Pack pack(fin);
        
    }
    
    //Shuffle
    void shuffle_pack() {
        if(shuffle) {
            pack.shuffle();
        }
        else {
            pack.reset();
        }
    }
        
    void deal_cards() {
        players[(dealerIndex+1)%4]->add_card(pack.deal_one());
        players[(dealerIndex+1)%4]->add_card(pack.deal_one());
        players[(dealerIndex+1)%4]->add_card(pack.deal_one());

        players[(dealerIndex+2)%4]->add_card(pack.deal_one());
        players[(dealerIndex+2)%4]->add_card(pack.deal_one());

        players[(dealerIndex+3)%4]->add_card(pack.deal_one());
        players[(dealerIndex+3)%4]->add_card(pack.deal_one());
        players[(dealerIndex+3)%4]->add_card(pack.deal_one());

        players[dealerIndex]->add_card(pack.deal_one());
        players[dealerIndex]->add_card(pack.deal_one());

        players[(dealerIndex+1)%4]->add_card(pack.deal_one());
        players[(dealerIndex+1)%4]->add_card(pack.deal_one());

        players[(dealerIndex+2)%4]->add_card(pack.deal_one());
        players[(dealerIndex+2)%4]->add_card(pack.deal_one());
        players[(dealerIndex+2)%4]->add_card(pack.deal_one());

        players[(dealerIndex+3)%4]->add_card(pack.deal_one());
        players[(dealerIndex+3)%4]->add_card(pack.deal_one());
        
        players[dealerIndex]->add_card(pack.deal_one());
        players[dealerIndex]->add_card(pack.deal_one());
        players[dealerIndex]->add_card(pack.deal_one());
    }

    //Make trump
    void make_trump_rounds() { 
        operator<<(cout,*players[dealerIndex]);
        cout << " deals" << endl;
        //Next card is upcard
        Card upcard = pack.deal_one();
        cout << upcard << " turned up" << endl;
        string order_up_suit = upcard.get_suit();
        int round = 1;
        bool trump_unchosen = true;
        int i = dealerIndex + 1;
        while(trump_unchosen) {
            if(players[i]->make_trump(upcard, (i == dealerIndex), 
            round, order_up_suit)) {
                cout << *players[i] << " orders up " << 
                order_up_suit << endl;
                cout << endl;
                if (round == 1) { 
                    players[dealerIndex]->add_and_discard(upcard);
                }
                trump_unchosen = false;
            }
            else {
                cout << *players[i] << " passes" << endl;
            }
            if(i == dealerIndex) {round++;}
            i = (i+1) % 4;
        }
        //save info on which team called up trump
        trump = order_up_suit;
        if(i == 0) {
            trump_maker_index = 3;
        }
        else {
            trump_maker_index = i-1;
        }
    }

    void play_a_trick() { 
        currentPlayer = leadPlayer;
        //player to the left of the dealer plays card
        led_card = players[leadPlayer]->lead_card(trump);
        operator<<(cout,led_card);
        cout << " led by " << *players[leadPlayer] << endl;;
        //that card is currently the highest
        highestCard = led_card;
        highestCardPlayer = leadPlayer;
        currentPlayer = (currentPlayer+1) % 4;
        //next player plays card
        for(int i = 1; i < NUM_PLAYERS; i++) { //leader+1, leader+2, leader+3
            compare_card = players[currentPlayer]->play_card(led_card,trump);
            operator<<(cout,compare_card);
            cout << " played by " << *players[currentPlayer] << endl;
            //checks which one is higher using Card_less
            if(Card_less(highestCard,compare_card,led_card,trump)) {
                highestCard = compare_card;
                highestCardPlayer = currentPlayer;
            }
            currentPlayer = (currentPlayer+1) % 4;
        }
    }

    void play_a_hand() {
        team1Tricks = 0;
        team2Tricks = 0;
        for(int j = 0; j < NUM_TRICKS; j++) {
            play_a_trick();
            cout << *players[highestCardPlayer] << " takes the trick" << 
            endl << endl;
            //whichever player has the highest card, their team takes trick
            string highestCardPlayer_name = 
                players[highestCardPlayer]->get_name();
            if((highestCardPlayer_name == team1[0]->get_name()) || 
                (highestCardPlayer_name == team1[1]->get_name())) {

                team1Tricks++;
            }
            else if((highestCardPlayer_name == team2[0]->get_name()) || 
                (highestCardPlayer_name == team2[1]->get_name())) {

                team2Tricks++;
            }
            //that player is the new leader for the next trick
            leadPlayer = highestCardPlayer;
        }
    }

    void update_scores() {
        //if team 1 called up trump
        //if team 2 did not call up trump
        string trump_maker = players[trump_maker_index]->get_name();
        if(team1[0]->get_name() == trump_maker || 
            team1[1]->get_name() == trump_maker) {
            if(team1Tricks == 5) {
                cout << *team1[0] << " and " << *team1[1]
                << " win the hand" << endl;
                cout << "march!" << endl;
                team1_score += 2;
            }
            else if(team1Tricks >= 3) {
                cout << *team1[0] << " and " << *team1[1]
                << " win the hand" << endl;
                team1_score++;
            }
            else if(team2Tricks >= 3) {
                cout << *team2[0] << " and " << *team2[1]
                << " win the hand" << endl;
                cout << "euchred!" << endl;
                team2_score += 2;
            }
        }

        //if team 2 called up trump
        //if team 1 did not call up trump
        if(team2[0]->get_name() == trump_maker || 
            team2[1]->get_name() == trump_maker) {
            
            if(team2Tricks == 5) {
                cout << *team2[0] << " and " << *team2[1]
                << " win the hand" << endl;
                cout << "march!" << endl;
                team2_score += 2;
            }
            else if(team2Tricks >= 3) {
                cout << *team2[0] << " and " << *team2[1]
                << " win the hand" << endl;
                team2_score++;
            }
            else if(team1Tricks >= 3) {
                cout << *team1[0] << " and " << *team1[1]
                << " win the hand" << endl;
                cout << "euchred!" << endl;
                team1_score += 2;
            }
        }

        //team1 is dealerIndex and dealerIndex+2
        //team2 is dealerIndex+1 and dealerIndex+3
        //PRINT CURRENT SCORE AFTER EACH HAND
        cout << *team1[0] << " and " << *team1[1]
                << " have " << team1_score << " points" << endl;
        cout << *team2[0] << " and " << *team2[1] 
                << " have " << team2_score << " points" << endl;
        cout << endl;

        if(team1_score >= max_score) {
            cout << *team1[0] << " and " 
            << *team1[1] << " win!" << endl;
        }
        else if(team2_score >= max_score) {
            cout << *team2[0] << " and " 
            << *team2[1] << " win!" << endl;
        }
    }

    void play_game() {
        while(team1_score < max_score && team2_score < max_score) {
            cout << "Hand " << Hand << endl;
            shuffle_pack();
            deal_cards();
            make_trump_rounds();
            play_a_hand();
            update_scores();
            dealerIndex = (dealerIndex + 1) % 4;
            leadPlayer = (dealerIndex + 1) % 4;
            Hand++;
        }
        //DELETE PLAYER OBJECTS
        /* for (int i = 0; i < int(players.size()); ++i) {
            delete players[i];
        } */
        for (int i = 0; i < NUM_PLAYERS; ++i) {
            delete players[i];
        } 
    }
};


int main(int argc, char *argv[]) {
    //COMMAND LINE
    string shuffle_arg = argv[2];
    string humanstring = "Human";
    string simplestring = "Simple";
    if ((argc != 12) || (atoi(argv[3]) < 0) || (atoi(argv[3]) > 100) || 
    ((shuffle_arg != "shuffle") && (shuffle_arg != "noshuffle")) || 
    ((argv[5] != simplestring) && (argv[5] != humanstring)) || 
    ((argv[7] != simplestring) && (argv[7] != humanstring)) || 
    ((argv[9] != simplestring) && (argv[9] != humanstring)) || 
    ((argv[11] != simplestring) && (argv[11] != humanstring))) {

        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    char* inName = argv[1];
    ifstream fin(inName);
    if (!fin.is_open()) {
        cout << "Error opening " << inName << endl;
        return 1;
    }

    for(int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;

    //RUN THE GAME HERE
    Game game(argv);
    game.play_game();
    
    return 0;
    
}