#include "pch.h"
#include <vector>
#include <random>
#include "../Polinom/Polinome.cpp"

using std::vector;

// ------------------------- Monome TESTS --------------------------------------
TEST(MonomeTest, MoreLessEqual) {
    Monome n1(1, 33); // 033
    Monome n2(1, 202);
    EXPECT_TRUE(n1 > n2); // в первую очередь порядок по степеням
    EXPECT_FALSE(n1 < n2);
    EXPECT_FALSE(n1 == n2);
    EXPECT_FALSE(n2 > n1);

    Monome n3(1, 522);
    Monome n4(1, 513);
    EXPECT_TRUE(n3 > n4);

    Monome n5(1, 120);
    Monome n6(1, 210);
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

TEST(ListTest, InsertTest) {
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

    std::uniform_int_distribution<> insert_count_dist(50, 1000);
	int insert_count = insert_count_dist(gen);
    for (int i = 0; i < insert_count; i++) {
        std::uniform_int_distribution<> insert_ind_dist(0, len);
		int insert_ind = insert_ind_dist(gen);
		int insert_val = value_dist(gen);
		v.insert(v.begin() + insert_ind, insert_val);
		List<int>::iterator it = l.begin();
        for(int j = 0; j < insert_ind; j++) {
            it++;
		}
		l.insert(it, insert_val);
		len++;
        
    }
    List<int>::iterator it = l.begin();
    for (size_t j = 0; j < v.size(); j++) {
        EXPECT_EQ(*it, v[j]);
        it++;
    }
}

TEST(ListTest, RandEraseTest) {
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

    std::uniform_int_distribution<> erase_count_dist(50, len);
    int erase_count = erase_count_dist(gen);
    for (int i = 0; i < erase_count; i++) {
        std::uniform_int_distribution<> erase_ind_dist(0, len-1);
        int erase_ind = erase_ind_dist(gen);
		//cout << "erase_ind: " << erase_ind << " len: " << len << endl;
        v.erase(v.begin() + erase_ind);
        List<int>::iterator it = l.begin();
        for (int j = 0; j < erase_ind; j++) {
            it++;
        }
        l.erase(it);
        len--;
    }
    List<int>::iterator it = l.begin();
    for (size_t j = 0; j < v.size(); j++) {
        EXPECT_EQ(*it, v[j]);
        it++;
    }
}

TEST(ListTest, ExtremeInsertEraseTest) {
    vector<int> v;
    List<int> l;
	v.push_back(1); l.push_back(1);
    v.push_back(2); l.push_back(2);
    v.push_back(3); l.push_back(3);
    v.push_back(4); l.push_back(4);
    v.push_back(5); l.push_back(5);

    EXPECT_NO_THROW(l.insert(l.begin(), 0));// вставка в начало
	v.insert(v.begin(), 0);
	EXPECT_NO_THROW(l.insert(l.end(), 6)); // вставка в конец
	v.insert(v.end(), 6);
	EXPECT_NO_THROW(l.erase(l.begin())); // удаление первого элемента
	v.erase(v.begin());
	EXPECT_ANY_THROW(l.erase(l.end())); // удаление end() итератора 
    List<int>::iterator it = l.begin();
    for (size_t j = 0; j < v.size(); j++) {
        EXPECT_EQ(*it, v[j]);
        it++;
    }

    List<int> l2;
    EXPECT_NO_THROW(l2.insert(l2.begin(), 1));
}


TEST(ListTest, SortTest) {
    vector<int> v;
    List<int> l;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> len_dist(100, 4000);
    std::uniform_int_distribution<> value_dist(INT_MIN, INT_MAX);
    int len = len_dist(gen);
    for (int j = 0; j < len; j++) {
        int val = value_dist(gen);
        v.push_back(val);
        l.push_back(val);
    }
    std::sort(v.begin(), v.end());
    l.sort();

    List<int>::iterator it = l.begin();
    for (size_t j = 0; j < v.size(); j++) {
        EXPECT_EQ(*it, v[j]);
        it++;
    }
}



//--------------------------------- Polinom TESTS --------------------------------



//TEST(PolinomTest, AdditionSimple) {
//    Polinom p1, p2;
//    p1.push_back(2, 101); // 2 xz
//    p2.push_back(3, 202); // 3 x2z2
//
//    Polinom res = p1 + p2;
//
//    EXPECT_NE(res.poly.head, nullptr);  // (202 > 101)
//    EXPECT_EQ(res.poly.head->power, 202);
//    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 3.0);
//
//    EXPECT_NE(res.poly.head->next, nullptr);
//    EXPECT_EQ(res.poly.head->next->power, 101);
//    EXPECT_DOUBLE_EQ(res.poly.head->next->coeff, 2.0);
//}
//
//TEST(PolinomTest, AdditionMerging) {
//    Polinom p1, p2;
//    p1.push_back(5, 303);
//    p1.push_back(1, 101);
//
//    p2.push_back(2, 303); // степень как у монома p1
//
//    Polinom res = p1 + p2;
//
//    // 7 303 , 1 101
//    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 7);
//    EXPECT_EQ(res.poly.head->power, 303);
//    EXPECT_EQ(res.poly.head->next->power, 101);
//}
//
//TEST(PolinomTest, SubtractionToZero) {
//    Polinom p1, p2;
//    p1.poly.push_back(10, 555);
//    p2.poly.push_back(10, 555);
//
//    Polinom res = p1 - p2;
//
//    EXPECT_EQ(res.poly.head, nullptr);
//}
//
//TEST(PolinomTest, ScalarMultiplication) {
//    Polinom p1;
//    p1.poly.push_back(2, 111);
//    p1.poly.push_back(-3, 222);
//
//    Polinom res = p1 * (-2);
//
//    // p1: -3 222, 2 111, после умножения: 6 222, -4 111
//    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 6);
//    EXPECT_DOUBLE_EQ(res.poly.head->next->coeff, -4);
//}
//
//TEST(PolinomTest, PolinomialMultiplication) {
//    // (x + 1) * (x - 1) = x^2 - 1
//    Polinom p1, p2;
//    p1.poly.push_back(1.0, 100); // x
//    p1.poly.push_back(1.0, 000); // 1
//
//    p2.poly.push_back(1.0, 100); // x
//    p2.poly.push_back(-1.0, 000); // -1
//
//    Polinom res = p1 * p2;
//
//    // 1 200, -1 000
//    ASSERT_NE(res.poly.head, nullptr);
//    EXPECT_EQ(res.poly.head->power, 200);
//    EXPECT_DOUBLE_EQ(res.poly.head->coeff, 1.0);
//
//    ASSERT_NE(res.poly.head->next, nullptr);
//    EXPECT_EQ(res.poly.head->next->power, 000);
//    EXPECT_DOUBLE_EQ(res.poly.head->next->coeff, -1.0);
//    EXPECT_EQ(res.poly.head->next->next, nullptr);
//}
//
//TEST(PolinomTest, MultiplicationDegreeOverflow) {
//    Polinom p1, p2;
//    p1.push_back(1.0, 900); // x^9
//    p2.push_back(1.0, 100); // x^1
//
//    // x^9 * x^1 = x^10 (px > 9)
//    EXPECT_THROW(p1 * p2, std::runtime_error);
//}
//
//TEST(PolinomTest, MathematicalOrderSorting) {
//    Polinom p;
//
//    p.push_back(1.0, 101); // max deg 1
//    p.push_back(2.0, 202); // max deg 2
//    p.push_back(3.0, 33); // max deg 3
//
//    // 33, 202, 101
//    Monome* curr = p.poly.head;
//    EXPECT_NE(curr, nullptr);
//    EXPECT_EQ(curr->power, 33);
//
//    curr = curr->next;
//    EXPECT_NE(curr, nullptr);
//    EXPECT_EQ(curr->power, 202);
//
//    curr = curr->next;
//    EXPECT_NE(curr, nullptr);
//    EXPECT_EQ(curr->power, 101);
//}