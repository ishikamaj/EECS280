// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

TEST(test_1) {
    List<int> list1;
    list1.push_front(2);
    list1.push_front(3);
    list1.push_front(1);
    list1.push_front(6);
    list1.push_front(8);
    list1.pop_front();
    //list1: 6 1 3 2


    List<int> list2;
    list2.push_back(6);
    list2.push_back(1);
    list2.push_back(3);
    list2.push_back(2);
    //list2: 6 1 3 2

    ASSERT_EQUAL(list1.size(), list2.size());
    ASSERT_EQUAL(list1.front(), 6);
    ASSERT_EQUAL(list1.back(), 2);
    
    //test 1
    List<int>::Iterator it2 = list2.begin();
    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        ASSERT_EQUAL(*it, *it2);
        ++it2;
    }
    
    list1.pop_front();
    list1.pop_front();
    //list1: 3 2 
    list2.clear();
    list2.push_front(2);
    list2.push_front(3);
    //list2: 3 2 

    ASSERT_EQUAL(list1.size(), list2.size());
    ASSERT_EQUAL(list1.front(), 3);
    ASSERT_EQUAL(list1.back(), 2);

    //test 2
    it2 = list2.begin();
    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        ASSERT_EQUAL(*it, *it2);
        ++it2;
    }

    list1.push_front(10);
    list1.push_front(7);
    list1.pop_front();
    //list1: 10 3 2
    list2.clear();
    list2.push_front(2);
    list2.push_front(3);
    list2.push_front(10);
    //list2: 10 3 2

    ASSERT_EQUAL(list1.size(), list2.size());
    ASSERT_EQUAL(list1.front(), 10);
    ASSERT_EQUAL(list1.back(), 2);

    //test 3
    it2 = list2.begin();
    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        ASSERT_EQUAL(*it, *it2);
        ++it2;
    }

    list1.push_back(8);
    list1.push_back(11);
    list1.push_back(13);
    list1.pop_front();
    list1.pop_front();
    list1.pop_front();
    //list1: 8 11 13

    list2.clear();
    list2.push_back(13);
    list2.push_front(11);
    list2.push_front(8);
    //list2: 8 11 13
    
    ASSERT_EQUAL(list1.size(), list2.size());
    ASSERT_EQUAL(list1.front(), 8);
    ASSERT_EQUAL(list1.back(), 13);

    //test 4
    it2 = list2.begin();
    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        //cout << *it << "  " << *it2 << endl;
        ASSERT_EQUAL(*it, *it2);
        ++it2;
    }
    //cout << "sizes: " << list1.size() << " " << list2.size() << endl;
}  

TEST(test_105) {
    List<int> list1;
    list1.push_back(3);

    List<int> list2;
    list2.push_back(3);

    //test 1
    List<int>::Iterator it2 = list2.begin();
    //cout << "list1 size: " << list1.size() << "\nlist2 size: " << list2.size() << endl;

    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        //cout << *it << " " << *it2 << endl;
        ASSERT_EQUAL(*it, *it2);
       // cout << "increase it2" << endl;
        ++it2;
    }

}


TEST(test_2) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_front(3);
    list1.push_back(4);
    list1.push_front(5);
    //list1: 5 3 2 1 4

    List<int> list2;
    list2 = list1;
    //list2: 5 3 2 1 4
    
    //test 1
    List<int>::Iterator it2 = list2.begin();

    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        ASSERT_EQUAL(*it, *it2);
        ++it2;
    }
     cout << "done checking" << endl;

    list1.pop_back();
    //list1: 5 3 2 1
    list2 = list1;
    //list2: 5 3 2 1

    //test 2
    it2 = list2.begin();
    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        //cout << *it << " " << *it2 << endl;
        ASSERT_EQUAL(*it, *it2);
       // cout << "increase it2" << endl;
        ++it2;
    } 
}

TEST(test_3) {
    cout << "TEST 3 start " << endl;
    List<int> list1;
    list1.push_back(31);
    list1.push_back(42);
    list1.push_front(63);
    list1.pop_back();
    list1.pop_front();
    list1.pop_back();
    list1.push_back(98);
    //list1: 98 

    List<int> list2;
    list2 = list1;
    //list2: 98

    ASSERT_EQUAL(list1.size(), list2.size());
    ASSERT_EQUAL(list2.front(), 98);
    ASSERT_EQUAL(list2.back(), 98);
    
    //test 1
    List<int>::Iterator it2 = list2.begin();

    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        ASSERT_EQUAL(*it, *it2);
        ++it2;
    }

    list1.push_back(9);
    list2.push_back(9);
    list2 = list1;
    //list1: 98 9
    //list2: 98 9
    
    //test 2
    it2 = list2.begin();

    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        ASSERT_EQUAL(*it, *it2);
        ++it2;
    }

    list1.push_back(42);
    list1.push_back(32);
    list1.pop_front();
    list1.push_back(56);
    list1.push_back(2);
    list1.pop_front();
    list1.pop_back();
    list1.push_back(92);
    list1.push_front(25);
    list1.pop_back();
    //list1: 25 42 32 56

    list2.clear();
    list2.push_back(32);
    list2.push_front(42);
    list2.push_front(25);
    list2.push_back(56);
    //list2: 25 42 32 56

    ASSERT_EQUAL(list1.size(), list2.size());
    ASSERT_EQUAL(list2.front(), 25);
    ASSERT_EQUAL(list2.back(), 56);
    
    //test 3
    it2 = list2.begin();

    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        ASSERT_EQUAL(*it, *it2);
        ++it2;
    }

}

TEST(test_4) {
    List<int> list1;
    list1.push_back(21);
    list1.push_back(342);
    list1.push_back(32);
    list1.push_back(74);
    list1.push_back(52);
    list1.push_back(73);
    //list1: 21 342 32 74 52 73

    List<int> list2;
    list2.push_front(21);
    list2.push_front(342);
    list2.push_front(32);
    list2.push_front(74);
    list2.push_front(52);
    list2.push_front(73);
    //list2: 73 52 74 32 342 21
    

    ASSERT_EQUAL(list1.size(), list2.size());
    
    //test 1
    List<int>::Iterator it2 = list2.begin();

    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        it2 = it;
        ASSERT_NOT_EQUAL(*it, *it2);
    }

}

TEST(test_5) {

    List<int> list1;
    list1.push_back(82);
    list1.push_back(36);
    list1.push_back(49);
    list1.push_back(62);
    list1.push_back(92);
    List<int>::Iterator insertIt = ++(++list1.begin());
    list1.insert(insertIt, 17);
    //list1: 82 36 17 49 62 92

    list1.erase(insertIt);
    //list1: 82 36 17 62 92
    
    List<int> list2;
    list2.push_front(92);
    list2.push_front(62);
    list2.push_front(17);
    list2.push_front(36);
    list2.push_front(82);

    List<int>::Iterator it2 = list2.begin();
    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        it2 = it;
        ASSERT_EQUAL(*it, *it2);
    }

}

TEST(test_6) {
     List<int> list1;
    list1.push_front(2);
    list1.push_front(3);
    list1.push_front(8);
    list1.pop_front();
    list1.pop_back();
    list1.pop_front();
    //list1: 
    ASSERT_TRUE(list1.empty());


    List<int> list2;
    list1.push_front(2);
    list1.push_back(3);
    list1.push_front(8);
    list1.pop_front();
    list1.pop_back();
    list1.pop_back();
    //list2:
    ASSERT_TRUE(list2.empty());

    list1.push_front(5);
    list1.pop_front();
    ASSERT_TRUE(list1.empty());

    list1.push_front(2);
    list1.pop_back();
    ASSERT_TRUE(list1.empty());

    list2.push_back(7);
    list2.pop_front();
    ASSERT_TRUE(list2.empty());

    list2.push_back(10);
    list2.pop_back();
    ASSERT_TRUE(list2.empty());

    list1.push_back(2);
    list1.push_front(3);
    list1.push_back(8);
    list1.clear();
    ASSERT_TRUE(list1.empty());
} 

TEST(test_7) {

    List<int> list1;
    list1.push_back(2);
    List<int>::Iterator insertIt = list1.begin();
    ++insertIt;
    list1.insert(insertIt, 17);
    list1.insert(insertIt, 34);
    insertIt = list1.begin();
    ++insertIt;
    ++insertIt;
    list1.insert(insertIt, 62);
    --insertIt;
    list1.insert(insertIt, 59);
    //list1: 2 17 59 62 34

    List<int> list2;
    list2.push_front(34);
    list2.push_front(62);
    list2.push_front(59);
    list2.push_front(17);
    list2.push_front(2);
    //list2: 2 17 59 62 34

    //test 1
    List<int>::Iterator it2 = list2.begin();
    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        it2 = it;
        ASSERT_EQUAL(*it, *it2);
    }

    List<int>::Iterator eraseIt = list1.begin();
    list1.erase(eraseIt);
    //list1: 17 59 62 34
    
    list2.clear();
    list2.push_front(34);
    list2.push_front(62);
    list2.push_front(59);
    list2.push_front(17);

    //test 2
    it2 = list2.begin();
    for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it) {
        it2 = it;
        ASSERT_EQUAL(*it, *it2);
    }
    
    ASSERT_EQUAL(list1.size(), list2.size());
    ASSERT_EQUAL(list1.back(), list2.back());
    
}


TEST(test_8) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
 
    List<int>::Iterator iter = list.begin();
    List<int>::Iterator start = iter;
    ++iter;
    List<int>::Iterator add = iter;
    bool a = (add == start);
    ASSERT_FALSE(a);
    --iter;
    bool b = (iter == start);
    ASSERT_TRUE(b);
    --iter;
    List<int>::Iterator subtract = iter;
    bool c = (subtract != start);
    ASSERT_TRUE(c);
} 


TEST_MAIN()
