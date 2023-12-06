// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * jisoo = Player_factory("Jisoo", "Simple");
    ASSERT_EQUAL("Jisoo", jisoo->get_name());

    Player * jennie = Player_factory("Jennie", "Simple");
    ASSERT_EQUAL("Jennie", jennie->get_name());

    Player * rose = Player_factory("Rose", "Simple");
    ASSERT_EQUAL("Rose", rose->get_name());
    
    Player * lisa = Player_factory("Lisa", "Simple");
    ASSERT_EQUAL("Lisa", lisa->get_name());

    delete jisoo;
    delete jennie;
    delete rose;
    delete lisa;
}

TEST(test_player_add_discard) {

    Card upcard(Card::RANK_ACE, Card::SUIT_HEARTS);
    string trump = Card::SUIT_CLUBS;
    Card led(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);

    Player * jisoo = Player_factory("Jisoo", "Simple");
    Card a(Card::RANK_QUEEN, Card::SUIT_SPADES);
    jisoo->add_card(a);
    jisoo->add_and_discard(upcard);
    ASSERT_EQUAL(upcard, jisoo->play_card(led, trump));

    Player * jennie = Player_factory("Jennie", "Simple");
    Card b(Card::RANK_NINE, Card::SUIT_SPADES);
    jennie->add_card(b);
    jennie->add_and_discard(upcard);
    ASSERT_EQUAL(upcard, jennie->play_card(led, trump));
    

    Player * rose = Player_factory("Rose", "Simple");
    Card c(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    rose->add_card(c);
    rose->add_and_discard(upcard);
    ASSERT_EQUAL(upcard, rose->play_card(led, trump));
    
    
    Player * lisa = Player_factory("Lisa", "Simple");
    Card d(Card::RANK_KING, Card::SUIT_HEARTS);
    lisa->add_card(d);
    lisa->add_and_discard(upcard);
    ASSERT_EQUAL(upcard, lisa->play_card(led, trump));
    
    Player * giselle = Player_factory("Giselle", "Simple");
    Card e(Card::RANK_JACK, Card::SUIT_SPADES);
    giselle->add_card(e);
    giselle->add_and_discard(upcard);
    ASSERT_EQUAL(upcard, giselle->play_card(led, trump));

    Card anotherUp(Card::RANK_JACK, Card::SUIT_SPADES);

    Player * winter = Player_factory("Winter", "Simple");
    Card f(Card::RANK_JACK, Card::SUIT_CLUBS);
    winter->add_card(f);
    winter->add_and_discard(anotherUp);
    ASSERT_EQUAL(anotherUp, winter->play_card(led, trump));

    delete jisoo;
    delete jennie;
    delete rose;
    delete lisa;
    delete giselle;
    delete winter;
}

TEST(test_player_play_card) {
    
    Card led(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    string trump = "Spades";
    
    //all trumps
    Player * karina = Player_factory("Karina", "Simple");
    karina->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    karina->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    karina->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    karina->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));
    karina->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    ASSERT_EQUAL(Card(Card::RANK_NINE, Card::SUIT_SPADES), 
        karina->play_card(led, trump));
    ASSERT_EQUAL(Card(Card::RANK_TEN, Card::SUIT_SPADES), 
        karina->play_card(led, trump));
    ASSERT_EQUAL(Card(Card::RANK_QUEEN, Card::SUIT_SPADES), 
        karina->play_card(led, trump));
    ASSERT_EQUAL(Card(Card::RANK_ACE, Card::SUIT_SPADES), 
        karina->play_card(led, trump));
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_CLUBS), 
        karina->play_card(led, trump));

    //no trumps
    Player * ningning = Player_factory("Ningning", "Simple");
    ningning->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS)); 
    ningning->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS)); 
    ningning->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    ningning->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS)); 
    ningning->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
    ASSERT_EQUAL(Card(Card::RANK_KING, Card::SUIT_HEARTS), 
        ningning->play_card(led, trump));
    led = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS), 
        ningning->play_card(led, trump));
    led = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS), 
        ningning->play_card(led, trump));
    led = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_HEARTS), 
        ningning->play_card(led, trump));
    ASSERT_EQUAL(Card(Card::RANK_TEN, Card::SUIT_CLUBS), 
        ningning->play_card(led, trump));

    //left and right bower
    Player * winter = Player_factory("Winter", "Simple");
    winter->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS)); 
    winter->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS)); 
    winter->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    winter->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS)); 
    winter->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    led = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card(Card::RANK_KING, Card::SUIT_HEARTS), 
        winter->play_card(led, trump));
    led = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS), 
        winter->play_card(led, trump));
    led = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card(Card::RANK_NINE, Card::SUIT_HEARTS), 
        winter->play_card(led, trump));
    led = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_CLUBS), 
        winter->play_card(led, trump));
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_SPADES), 
        winter->play_card(led, trump));

    //tie breaker and led/trump = same
    Player * giselle = Player_factory("Giselle", "Simple");
    giselle->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS)); 
    giselle->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS)); 
    giselle->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS)); 
    giselle->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS)); 
    giselle->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES)); 
    led = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card(Card::RANK_KING, Card::SUIT_HEARTS), 
        giselle->play_card(led, trump));
    led = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card(Card::RANK_JACK, Card::SUIT_CLUBS), 
        giselle->play_card(led, trump));
    led = Card(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card(Card::RANK_NINE, Card::SUIT_SPADES), 
        giselle->play_card(led, trump));
    led = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card(Card::RANK_NINE, Card::SUIT_HEARTS), 
        giselle->play_card(led, trump));
    ASSERT_EQUAL(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS), 
        giselle->play_card(led, trump));

    delete winter;
    delete giselle;
    delete karina;
    delete ningning;
}

TEST(test_player_lead) {

    string trump = Card::SUIT_CLUBS;

    Player * jisoo = Player_factory("Jisoo", "Simple");
    Card a(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card b(Card::RANK_JACK, Card::SUIT_SPADES);
    jisoo->add_card(a);
    jisoo->add_card(b);
    ASSERT_EQUAL(a, jisoo->lead_card(trump));
    

    Player * jennie = Player_factory("Jennie", "Simple");
    Card c(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card d(Card::RANK_ACE, Card::SUIT_HEARTS);
    jennie->add_card(c);
    jennie->add_card(d);
    ASSERT_EQUAL(d, jennie->lead_card(trump));
    

    Player * rose = Player_factory("Rose", "Simple");
    Card e(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card f(Card::RANK_TEN, Card::SUIT_HEARTS);
    rose->add_card(e);
    rose->add_card(f);
    ASSERT_EQUAL(e, rose->lead_card(trump));    
    
    Player * lisa = Player_factory("Lisa", "Simple");
    Card g(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card h(Card::RANK_JACK, Card::SUIT_SPADES);
    lisa->add_card(g);
    lisa->add_card(h);
    ASSERT_EQUAL(g, lisa->lead_card(trump));

    Player * giselle = Player_factory("Giselle", "Simple");
    Card i(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card j(Card::RANK_JACK, Card::SUIT_SPADES);
    giselle->add_card(i);
    giselle->add_card(j);
    ASSERT_EQUAL(j, giselle->lead_card(trump));

    Player * winter = Player_factory("Winter", "Simple");
    Card k(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card l(Card::RANK_JACK, Card::SUIT_SPADES);
    winter->add_card(k);
    winter->add_card(l);
    ASSERT_EQUAL(k, winter->lead_card(trump));

    delete jisoo;
    delete jennie;
    delete rose;
    delete lisa;
    delete giselle;
    delete winter;
}

TEST(test_player_led_trump) {
    //trump: clubs
    //led card: king of clubs
    //player's hand: Jack spades (left bower), Queen of clubs, 9 spades, 
    //9 hearts, Queen clubs
    //possible bug: 
    //jeff should play highest card that matches led card: jack of spades
    Player * jeff = Player_factory("Jeff", "Simple");
    string trump = Card::SUIT_CLUBS;
    Card led_card(Card::RANK_KING, Card::SUIT_CLUBS);
    Card a(Card::RANK_JACK, Card::SUIT_SPADES);
    Card b(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card d(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card e(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    jeff->add_card(a);
    jeff->add_card(b);
    jeff->add_card(c);
    jeff->add_card(d);
    jeff->add_card(e);
    Card jeff_card = jeff->play_card(led_card, trump);
    ASSERT_EQUAL(a, jeff_card);

    //test if player can not follow suit holding the left bower
    //if it thinks left bower is not clubs, it will play the lowest card
    //lowest card: 9 hearts
    //should play: Jack spades
    //led card: King clubs
    //hand: 9 hearts, King hearts, Ten diamonds, Ace spades, Jack spades
    Card f(Card::RANK_KING, Card::SUIT_HEARTS);
    Card g(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card h(Card::RANK_ACE, Card::SUIT_SPADES);
    Player * abed = Player_factory("Abed", "Simple");
    abed->add_card(d);
    abed->add_card(f);
    abed->add_card(g);
    abed->add_card(h);
    abed->add_card(a);
    Card abed_card = abed->play_card(led_card, trump);
    ASSERT_EQUAL(a, abed_card);

    delete jeff;
    delete abed;

}

TEST(test_player_make_trump) {
    
    Card a(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card b(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card d(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card e(Card::RANK_TEN, Card::SUIT_SPADES);
    Card f(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card g(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card h(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card i(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card j(Card::RANK_JACK, Card::SUIT_SPADES);
    Card k(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card l(Card::RANK_TEN, Card::SUIT_HEARTS);

    Card upcard(Card::RANK_TEN, Card::SUIT_CLUBS);
    string orderUpSuit = "Hearts";


    Player * jisoo = Player_factory("Jisoo", "Simple");
    jisoo->add_card(a);
    jisoo->add_card(c);
    jisoo->add_card(g);
    jisoo->add_card(h);
    jisoo->add_card(i);

    ASSERT_TRUE(jisoo->make_trump(upcard, false, 1, orderUpSuit));

    Player * jennie = Player_factory("Jennie", "Simple");
    jennie->add_card(d);
    jennie->add_card(e);
    jennie->add_card(b);
    jennie->add_card(c);
    jennie->add_card(i);
    ASSERT_TRUE(jennie->make_trump(upcard, true, 2, orderUpSuit));
    

    Player * rose = Player_factory("Rose", "Simple");
    rose->add_card(b);
    rose->add_card(e);
    rose->add_card(c);
    rose->add_card(d);
    rose->add_card(f);
    ASSERT_TRUE(!rose->make_trump(upcard, false, 1, orderUpSuit));
    
    
    Player * lisa = Player_factory("Lisa", "Simple");
    lisa->add_card(b);
    lisa->add_card(e);
    lisa->add_card(c);
    lisa->add_card(d);
    lisa->add_card(f);
    ASSERT_TRUE(lisa->make_trump(upcard, false, 2, orderUpSuit));

    Player * karina = Player_factory("Karina", "Simple");
    karina->add_card(g);
    karina->add_card(b);
    karina->add_card(c);
    karina->add_card(d);
    karina->add_card(f);
    ASSERT_TRUE(karina->make_trump(upcard, true, 2, orderUpSuit));

    Player * ningning = Player_factory("Ningning", "Simple");
    ningning->add_card(j);
    ningning->add_card(b);
    ningning->add_card(c);
    ningning->add_card(a);
    ningning->add_card(f);
    ASSERT_TRUE(!ningning->make_trump(upcard, true, 1, orderUpSuit));
    
    Player * winter = Player_factory("Winter", "Simple");
    winter->add_card(a);
    winter->add_card(e);
    winter->add_card(f);
    winter->add_card(l);
    winter->add_card(k);
    ASSERT_TRUE(winter->make_trump(upcard, true, 2, orderUpSuit));

    delete jisoo;
    delete jennie;
    delete rose;
    delete lisa;
    delete karina;
    delete ningning;
    delete winter;
}

TEST_MAIN()
