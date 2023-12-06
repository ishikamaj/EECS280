// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;


TEST(test_basics) {
    //inserting, empty, height, size, copying
    BinarySearchTree<int> tree1;

    ASSERT_EQUAL(tree1.height(), 0);
    ASSERT_EQUAL(tree1.size(), 0);
    ASSERT_TRUE(tree1.empty());

    tree1.insert(8);
    tree1.insert(-2);
    tree1.insert(7);

    ASSERT_EQUAL(tree1.height(), 3);
    ASSERT_EQUAL(tree1.size(), 3);
    ASSERT_TRUE(!tree1.empty());

    tree1.insert(9);

    ASSERT_EQUAL(tree1.height(), 3);
    ASSERT_EQUAL(tree1.size(), 4);

    BinarySearchTree<int> tree2(tree1);
    ASSERT_TRUE(!tree2.empty());
    ASSERT_EQUAL(tree1.height(), tree2.height());
    ASSERT_EQUAL(tree1.size(), tree2.size());

    tree2.insert(6);
    tree2.insert(21);
    tree2.insert(13);
    tree2.insert(16);

    ASSERT_EQUAL(tree2.height(), 5);
    ASSERT_EQUAL(tree2.size(), 8);

    BinarySearchTree<int> tree3(tree2);
    ASSERT_TRUE(!tree3.empty());
    ASSERT_EQUAL(tree2.height(), tree3.height());
    ASSERT_EQUAL(tree2.size(), tree3.size());

    BinarySearchTree<int> tree4;
    tree4 = tree3;
    ASSERT_TRUE(!tree4.empty());
    ASSERT_EQUAL(tree3.height(), tree4.height());
    ASSERT_EQUAL(tree3.size(), tree4.size());
}

TEST(test_min_max) {
    BinarySearchTree<int> tree1;

    ASSERT_EQUAL(tree1.min_element(), tree1.end());
    ASSERT_EQUAL(tree1.min_element(), tree1.begin());

    tree1.insert(9);

    ASSERT_EQUAL(*tree1.min_element(), 9);
    ASSERT_EQUAL(*tree1.max_element(), 9);

    tree1.insert(-22);
    tree1.insert(36);

    ASSERT_EQUAL(*tree1.min_element(), -22);
    ASSERT_EQUAL(*tree1.max_element(), 36);

    tree1.insert(31);

    ASSERT_EQUAL(*tree1.max_element(), 36);

    BinarySearchTree<int> tree2;
    tree2.insert(10);
    ASSERT_EQUAL(*tree2.max_element(), 10);
    ASSERT_EQUAL(*tree2.min_element(), 10);

    tree2.insert(14);
    ASSERT_EQUAL(*tree2.max_element(), 14);
    ASSERT_EQUAL(*tree2.min_element(), 10);

    tree2.insert(27);
    ASSERT_EQUAL(*tree2.max_element(), 27);
    ASSERT_EQUAL(*tree2.min_element(), 10);

    tree2.insert(106);
    ASSERT_EQUAL(*tree2.max_element(), 106);
    ASSERT_EQUAL(*tree2.min_element(), 10);

    BinarySearchTree<int> tree3;
    tree3.insert(-2);
    ASSERT_EQUAL(*tree3.max_element(), -2);
    ASSERT_EQUAL(*tree3.min_element(), -2);

    tree3.insert(-8);
    ASSERT_EQUAL(*tree3.max_element(), -2);
    ASSERT_EQUAL(*tree3.min_element(), -8);

    tree3.insert(-22);
    ASSERT_EQUAL(*tree3.max_element(), -2);
    ASSERT_EQUAL(*tree3.min_element(), -22);

    tree3.insert(-65);
    ASSERT_EQUAL(*tree3.max_element(), -2);
    ASSERT_EQUAL(*tree3.min_element(), -65);
}

TEST(test_min_greater) {
    BinarySearchTree<int> tree1;

    tree1.insert(12);
    tree1.insert(8);
    tree1.insert(16);
    tree1.insert(14);
    tree1.insert(10);
    tree1.insert(6);

    ASSERT_EQUAL(*tree1.min_greater_than(10), 12);
    ASSERT_EQUAL(*tree1.min_greater_than(12), 14);
    ASSERT_EQUAL(*tree1.min_greater_than(6), 8);

    BinarySearchTree<int> tree2;

    tree2.insert(3);
    tree2.insert(20);
    tree2.insert(6);
    tree2.insert(18);
    tree2.insert(8);
    tree2.insert(14);

    ASSERT_EQUAL(*tree2.min_greater_than(18), 20);
    ASSERT_EQUAL(*tree2.min_greater_than(8), 14);
    ASSERT_EQUAL(*tree2.min_greater_than(6), 8);
}

TEST(test_inorder) {
    BinarySearchTree<int> tree1;
    ostringstream os;
    tree1.traverse_inorder(os);
    ASSERT_EQUAL(os.str(), "");
    tree1.insert(9);
    tree1.insert(7);
    tree1.insert(10);
    tree1.traverse_inorder(os);
    cout << os.str() << endl << endl;
    ASSERT_EQUAL(os.str(), "7 9 10 ");

    BinarySearchTree<int> tree2;
    ostringstream os2;
    tree2.traverse_inorder(os2);
    ASSERT_EQUAL(os2.str(), "");
    tree2.insert(-82);
    tree2.insert(0);
    tree2.insert(70);
    tree2.traverse_inorder(os2);
    cout << os2.str() << endl << endl;
    ASSERT_EQUAL(os2.str(), "-82 0 70 ");
}

TEST(test_preorder) {
    BinarySearchTree<int> tree1;
    ostringstream os;
    tree1.traverse_preorder(os);
    ASSERT_EQUAL(os.str(), "");
    tree1.insert(9);
    tree1.insert(-21);
    tree1.insert(16);
    tree1.traverse_preorder(os);
    cout << os.str() << endl << endl;
    ASSERT_EQUAL(os.str(), "9 -21 16 ");

    BinarySearchTree<int> tree2;
    ostringstream os2;
    tree2.traverse_preorder(os2);
    ASSERT_EQUAL(os2.str(), "");
    tree2.insert(23);
    tree2.insert(-32);
    tree2.insert(-28);
    tree2.insert(22);
    tree2.traverse_preorder(os2);
    cout << os2.str() << endl << endl;
    ASSERT_EQUAL(os2.str(), "23 -32 -28 22 ");
}

TEST(test_sort_invar) {
    BinarySearchTree<int> tree1;
    ASSERT_TRUE(tree1.check_sorting_invariant());
    tree1.insert(9);
    tree1.insert(23);
    tree1.insert(25);
    tree1.insert(-234);
    ASSERT_TRUE(tree1.check_sorting_invariant());

    BinarySearchTree<int>::Iterator it;

    BinarySearchTree<int> tree2;
    ASSERT_TRUE(tree2.check_sorting_invariant());
    tree2.insert(8);
    it = tree2.insert(10);
    *it = 4;
    ASSERT_FALSE(tree2.check_sorting_invariant());
    *it = 9;
    it = tree2.insert(3);
    *it = 10;
    ASSERT_FALSE(tree2.check_sorting_invariant());
    
    BinarySearchTree<int> tree3;
    tree3.insert(7);
    tree3.insert(5);
    tree3.insert(10);
    tree3.insert(6);
    tree3.insert(9);
    it = tree3.max_element();
    *it = -6;
    ASSERT_FALSE(tree3.check_sorting_invariant());
    it = tree3.min_element();
    *it = 23;
    ASSERT_FALSE(tree3.check_sorting_invariant());
}

TEST_MAIN()
