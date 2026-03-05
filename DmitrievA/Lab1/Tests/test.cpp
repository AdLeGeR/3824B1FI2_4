#include "pch.h"
#include <vector>
#include <random>
#include "../Polinom/Polinom.h"

using std::vector;

// ------------------------- Monome TESTS --------------------------------------
TEST(MonomeTest, MoreLessEqual) {
    Monome n1(33, 1); // 033
    Monome n2(202, 1.0);
    EXPECT_TRUE(n1 > n2); // в первую очередь порядок по степеням
    EXPECT_FALSE(n1 < n2);
    EXPECT_FALSE(n1 == n2);
    EXPECT_FALSE(n2 > n1);

    Monome n3(513, 1);
    Monome n4(522, 1);
    EXPECT_TRUE(n3 > n4);

    Monome n5(120, 1);
    Monome n6(210, 1);
    EXPECT_TRUE(n6 > n5); // если одинаковые степени, порядок лексический (X > Y > Z)
}

// -------------------------- LIST TESTS -----------------------------------------------

TEST(ListTest, PushBack_And_Iterator) {
    vector<int> v;
	List<int> l;
    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> len_dist(100, 1000);
    std::uniform_int_distribution<> value_dist(INT_MIN, INT_MAX);
    int len = len_dist(gen);
    for (int j = 0; j < len; j++) {
        int val = value_dist(gen);
        v.push_back(val);
        l.push_back(val);
    }
    List<int>::iterator it = l.begin();
    for (size_t j = 0; j < v.size(); j++) {
        EXPECT_EQ(*it, v[j]);
        it++;
    }
}

TEST(ListTest, CopyConstructor) {
    List<int> l1;
    l1.simple_push_back(1, 100);
    l1.simple_push_back(2, 200);

    List l2 = l1;

    EXPECT_EQ(l2.head->power, 100);
    EXPECT_EQ(l2.tail->power, 200);


    l2.head->coeff = 99.9;
    EXPECT_NE(l1.head->coeff, l2.head->coeff);


    EXPECT_EQ(l2.tail->prev, l2.head);
    EXPECT_EQ(l2.head->next, l2.tail);
}

TEST(ListTest, Assignment) {
    List<int> l1, l2;
    l1.push_back(1);
    l2.push_back(2);

    l2 = l1;

    EXPECT_EQ(l2.head->power, 100);
    EXPECT_EQ(l2.head->next, nullptr);

    l2 = l2;                              // самоприсваивание
    EXPECT_EQ(l2.head->power, 100);
}

//--------------------------------- Polinom TESTS --------------------------------

TEST(PolinomTest, AdditionSimple) {
    Polinom p1, p2;
    p1.push_back(2, 101); // 2 xz
    p2.push_back(3, 202); // 3 x2z2

    Polinom res = p1 + p2;

    EXPECT_NE(res.poly.head, nullptr);  // (202 > 101)
    EXPECT_EQ(res.poly.head->power, 202);
    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 3.0);

    EXPECT_NE(res.poly.head->next, nullptr);
    EXPECT_EQ(res.poly.head->next->power, 101);
    EXPECT_DOUBLE_EQ(res.poly.head->next->coeff, 2.0);
}

TEST(PolinomTest, AdditionMerging) {
    Polinom p1, p2;
    p1.push_back(5, 303);
    p1.push_back(1, 101);

    p2.push_back(2, 303); // степень как у монома p1

    Polinom res = p1 + p2;

    // 7 303 , 1 101
    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 7);
    EXPECT_EQ(res.poly.head->power, 303);
    EXPECT_EQ(res.poly.head->next->power, 101);
}

TEST(PolinomTest, SubtractionToZero) {
    Polinom p1, p2;
    p1.poly.push_back(10, 555);
    p2.poly.push_back(10, 555);

    Polinom res = p1 - p2;

    EXPECT_EQ(res.poly.head, nullptr);
}

TEST(PolinomTest, ScalarMultiplication) {
    Polinom p1;
    p1.poly.push_back(2, 111);
    p1.poly.push_back(-3, 222);

    Polinom res = p1 * (-2);

    // p1: -3 222, 2 111, после умножения: 6 222, -4 111
    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 6);
    EXPECT_DOUBLE_EQ(res.poly.head->next->coeff, -4);
}

TEST(PolinomTest, PolinomialMultiplication) {
    // (x + 1) * (x - 1) = x^2 - 1
    Polinom p1, p2;
    p1.poly.push_back(1.0, 100); // x
    p1.poly.push_back(1.0, 000); // 1

    p2.poly.push_back(1.0, 100); // x
    p2.poly.push_back(-1.0, 000); // -1

    Polinom res = p1 * p2;

    // 1 200, -1 000
    ASSERT_NE(res.poly.head, nullptr);
    EXPECT_EQ(res.poly.head->power, 200);
    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 1.0);

    ASSERT_NE(res.poly.head->next, nullptr);
    EXPECT_EQ(res.poly.head->next->power, 000);
    EXPECT_DOUBLE_EQ(res.poly.head->next->coeff, -1.0);
    EXPECT_EQ(res.poly.head->next->next, nullptr);
}

TEST(PolinomTest, MultiplicationDegreeOverflow) {
    Polinom p1, p2;
    p1.push_back(1.0, 900); // x^9
    p2.push_back(1.0, 100); // x^1

    // x^9 * x^1 = x^10 (px > 9)
    EXPECT_THROW(p1 * p2, std::runtime_error);
}

TEST(PolinomTest, MathematicalOrderSorting) {
    Polinom p;

    p.push_back(1.0, 101); // max deg 1
    p.push_back(2.0, 202); // max deg 2
    p.push_back(3.0, 33); // max deg 3

    // 33, 202, 101
    Monome* curr = p.poly.head;
    EXPECT_NE(curr, nullptr);
    EXPECT_EQ(curr->power, 33);

    curr = curr->next;
    EXPECT_NE(curr, nullptr);
    EXPECT_EQ(curr->power, 202);

    curr = curr->next;
    EXPECT_NE(curr, nullptr);
    EXPECT_EQ(curr->power, 101);
}