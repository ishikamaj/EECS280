// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());

    Card d;
    ASSERT_EQUAL(Card::RANK_TWO, d.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, d.get_suit());
}

TEST(test_card_face) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(c.is_face());

    Card d(Card::RANK_QUEEN, Card::SUIT_SPADES);
    ASSERT_TRUE(d.is_face());

    Card e(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_TRUE(!e.is_face());
}

TEST(test_card_bower) {
    string trump = Card::SUIT_DIAMONDS;

    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c.is_right_bower(trump));
    ASSERT_TRUE(!c.is_left_bower(trump));
    ASSERT_TRUE(c.is_trump(trump));

    Card d(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(!d.is_right_bower(trump));
    ASSERT_TRUE(!d.is_left_bower(trump));
    ASSERT_TRUE(d.is_trump(trump));

    Card e(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(!e.is_right_bower(trump));
    ASSERT_TRUE(e.is_left_bower(trump));
    ASSERT_TRUE(e.is_trump(trump));

    Card f(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(!f.is_right_bower(trump));
    ASSERT_TRUE(!f.is_left_bower(trump));
    ASSERT_TRUE(!f.is_trump(trump));
}

TEST(test_card_operators) {
    Card a(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card b(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(a < b);
    ASSERT_TRUE(!(a > b));
    ASSERT_TRUE(!(a >= b));
    ASSERT_TRUE(a != b);

    Card c(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card d(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(!(c > d));
    ASSERT_TRUE(c < d);
    ASSERT_TRUE(c <= d);
    ASSERT_TRUE(!(c == d));

    ASSERT_TRUE(!(a < c));
    ASSERT_TRUE(!(a > c));
    ASSERT_TRUE(a >= c);
    ASSERT_TRUE(a <= c);
    ASSERT_TRUE(a == c);

}

TEST(test_card_nextSuit) {
    Card a(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card b(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_KING, Card::SUIT_SPADES);
    Card d(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(a.get_suit()), Card::SUIT_SPADES);
    ASSERT_EQUAL(Suit_next(b.get_suit()), Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(c.get_suit()), Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(d.get_suit()), Card::SUIT_DIAMONDS);
}

TEST(test_card_cardLess) {
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card d(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card e(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card f(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card g(Card::RANK_TEN, Card::SUIT_SPADES);
    Card h(Card::RANK_NINE, Card::SUIT_SPADES);
    
    string trump = Card::SUIT_CLUBS;
    Card led = f;

    ASSERT_TRUE(!Card_less(a, c, trump));
    ASSERT_TRUE(Card_less(c, a, trump));
    ASSERT_TRUE(!Card_less(a, d, trump));
    ASSERT_TRUE(!Card_less(a, e, trump));
    ASSERT_TRUE(Card_less(b, d, trump)); 

    ASSERT_TRUE(Card_less(b, d, led, trump));
    ASSERT_TRUE(!Card_less(a, e, led, trump));
    ASSERT_TRUE(!Card_less(c, d, led, trump));
    ASSERT_TRUE(Card_less(b, g, led, trump));
    ASSERT_TRUE(Card_less(h, b, led, trump));
}


TEST_MAIN()
