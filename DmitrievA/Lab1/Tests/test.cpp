#include "pch.h"
#include <vector>
#include <random>
#include "../Polinom/Polinome.cpp"

using std::vector;


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

TEST(MonomeTest, RandomEqual) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> power(0, 9);
	std::uniform_real_distribution<> coeff(-1000, 1000);
    for (int i = 0; i < 1000; i++) {
        int pow = power(gen) * 100 + power(gen) * 10 + power(gen);
        double co = coeff(gen);
        Monome n1(co, pow);
        Monome n2(co, pow);
        EXPECT_TRUE(n1 == n2);
	}
}

TEST(MonomeTest, RandomMinus) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> power(0, 9);
    std::uniform_real_distribution<> coeff(-1000, 1000);
    for (int i = 0; i < 1000; i++) {
        int pow = power(gen) * 100 + power(gen) * 10 + power(gen);
        double co = coeff(gen);
        Monome n1(-co, pow);
        Monome n2(co, pow);
        EXPECT_TRUE(n1 == -n2);
    }
}

TEST(MonomeTest, RandomMultiplication) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> power(0, 9);
    std::uniform_real_distribution<> coeff(-1000, 1000);
    std::uniform_real_distribution<> num(-100, 100);
    for (int i = 0; i < 1000; i++) {
        int pow = power(gen) * 100 + power(gen) * 10 + power(gen);
        double co = coeff(gen);
        double n = num(gen);
        Monome m(co, pow);
        EXPECT_EQ(Monome(co*n, pow), m * n);
    }
}

TEST(MonomeTest, RandomMultiplicationMonome) {
    std::random_device rd;
	int seed = rd(); // фиксируем сид для воспроизводимости теста
	cout << "seed: " << seed << endl;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> power1(0, 9);
    std::uniform_real_distribution<> coeff(-1000, 1000);
    std::uniform_real_distribution<> num(-100, 100);
    for (int i = 0; i < 1000; i++) {
        int pow11 = power1(gen);
        int pow12 = power1(gen);
        int pow13 = power1(gen);
        std::uniform_int_distribution<> power21(0, 9 - pow11);
        std::uniform_int_distribution<> power22(0, 9 - pow12);
        std::uniform_int_distribution<> power23(0, 9 - pow13);
        int pow21 = power21(gen);
        int pow22 = power22(gen);
        int pow23 = power23(gen);
        double c1 = coeff(gen);
        double c2 = coeff(gen);
        Monome m1(c1, pow11*100+pow12*10+pow13);
        Monome m2(c2, pow21 * 100 + pow22 * 10 + pow23);
        Monome m3(c1*c2, pow11 * 100 + pow12 * 10 + pow13 + pow21 * 100 + pow22 * 10 + pow23);
        EXPECT_EQ(m1*m2, m3);
    }
}

TEST(MonomeTest, MultiplicationOverflow) {
    Monome m1(1, 900);
    Monome m2(1, 100);
    EXPECT_THROW(m1 * m2, const char*);
}
TEST(MonomeTest, InvalidDegree) {
    EXPECT_THROW(Monome(1, -1), const char*);
    EXPECT_THROW(Monome(1, 1000), const char*);
}




// ------------------------- Polinom TESTS --------------------------------------

// Вспомогательная локальная функция для безопасного временного перенаправления std::cin
static void readPolinomFromString(Polinom& p, const std::string& s) {
    std::istringstream iss(s);
    std::streambuf* old = std::cin.rdbuf(iss.rdbuf());
    try {
        std::cin >> p;
    }
    catch (...) {
        std::cin.rdbuf(old);
        throw;
    }
    std::cin.rdbuf(old);
}

TEST(PolinomTest, ConstructorAndScalarMultiply) {
    Polinom p(5.0);
    Polinom r = p * 2.0;
    std::ostringstream oss;
    oss << r;
    // должен вывести коэффициент 10 (степень 0, печатается просто число) + пробел и +
    EXPECT_EQ(oss.str(), std::string("10 + "));
}

TEST(PolinomTest, AdditionSimpleInput) {
    // оба многочлена заданы двумя мономами: (3 x^2) + (4 x) и (1 x^2) + (-4 x)
    Polinom a, b;
    // формат: n coeff degree coeff degree ...
    readPolinomFromString(a, "2 3 200 4 100");
    readPolinomFromString(b, "2 1 200 -4 100");
    Polinom s = a + b;
    std::ostringstream oss;
    oss << s;
    // ожидаем суммирование коэффициентов степеней 200: 3+1=4, степени 100: 4+(-4)=0 -> исчезает
    EXPECT_EQ(oss.str(), std::string("4x^2 + "));
}

TEST(PolinomTest, MultiplyPolynomials) {
    // p = 2 x ; q = 3 y  => p*q = 6 x y
    Polinom p, q;
    readPolinomFromString(p, "1 2 100"); // coeff 2 degree 100 -> x^1
    readPolinomFromString(q, "1 3 010"); // coeff 3 degree 010 -> y^1
    Polinom prod = p * q;
    std::ostringstream oss;
    oss << prod;
    EXPECT_EQ(oss.str(), std::string("6x^1y^1 + "));
}

TEST(PolinomTest, MultiplyOverflowThrows) {
    Polinom p, q;
    // degrees chosen so that digit-wise sum exceeds 9 -> Monome::operator* throws
    readPolinomFromString(p, "1 1 900");
    readPolinomFromString(q, "1 1 200");
    EXPECT_THROW(p * q, const char*);
}

TEST(PolinomTest, InvalidMonomeInputThrows) {
    Polinom p;
    // один моном с некорректной степенью -1 должен вызвать исключение при вводе
    EXPECT_THROW(readPolinomFromString(p, "1 1 -1"), const char*);
}
