#include "pch.h"
#include "Header.h"
#include "Realisation.cpp"
#include <sstream>

TEST(TestNameMonomial, TestNameOperators) {
	Monomial M1(12, 123), M2(15, 102);
	EXPECT_TRUE(M1 < M2);
	EXPECT_TRUE(M1 == M1);
	EXPECT_TRUE(M1 != M2);
}

TEST(TestNameList, TestName) {
	my_list L1, L2;
	EXPECT_TRUE(L1.empty());
	Monomial M1(12, 123), M2(15, 102);
	EXPECT_NO_THROW({
	L1.emplace_back(12, 123);
	L1.emplace_back(16, 101);
	L1.emplace_back(M1);
	L1.emplace_back(M2);
	L2 = L1;
		});
}

TEST(TestNameInitialisation, TestNameConstructors) {
	EXPECT_NO_THROW({
		Polinomial P1("3 111 4 121 7 430");
		Polinomial P2("-6 100 5 404 9 123");
		Polinomial P3("-7 0 -13 105 -6 11");
		Polinomial P4;
		Polinomial P5(P1);
		});
	EXPECT_ANY_THROW({
		Polinomial P1("4 1023 7 1200");
		});
	EXPECT_ANY_THROW({
		Polinomial P1("34 -13 90 123");
		});
	EXPECT_ANY_THROW({
		Polinomial P1("56 34 5 -200");
		});
}

TEST(TestNameOperatorsEquality, TestNameOperators12) {
	Polinomial P1("1 123 4 456 7 789");
	Polinomial P2(P1);
	EXPECT_EQ(P1, P1);
	EXPECT_EQ(P1, P2);
	Polinomial P3("1 123 4 456 7 789");
	EXPECT_EQ(P1, P3);
	Polinomial P4("1 123 4 456");
	EXPECT_TRUE(P4 != P1);
	Polinomial P5;
	EXPECT_TRUE(P5 != P2);
	Polinomial P6("1 123 2 456 3 789 2 456 4 789");
	EXPECT_EQ(P1, P6);
}

TEST(TestNameOperatorsEquation, TestNameOperators3) {
	Polinomial P1("1 123 4 456 7 789");
	Polinomial P2;
	P2 = P1;
	EXPECT_EQ(P1, P2);
	Polinomial P3(P1);
	EXPECT_EQ(P3, P2);
}

TEST(TestNameOperatorsAdditionSubtraction, TestNameOperators4) {
	Polinomial P1("5 120 6 314 7.8 100");
	Polinomial P2("1.45 100 56 120");
	Polinomial P3("9.25 100 61 120 6 314");
	EXPECT_EQ(P3, P1 + P2);
	EXPECT_EQ(P1, P3 - P2);
	EXPECT_EQ(P2, P3 - P1);
	Polinomial P4("13 111 15.52 150");
	Polinomial P5("15 167 14.4 0");
	Polinomial P6("-14.4 0 -15 167 15.52 150 13 111");
	EXPECT_EQ(P6, P4 - P5);
	EXPECT_EQ(P6 - P6, P5 - P5);
}

TEST(TestNameOperatorsMultiplicationByConstant, TestNameOperators5) {
	Polinomial P1("5 120 6 314 7.8 100");
	Polinomial P2("1.45 100 56 120");
	Polinomial P3("50 120 60 314 78 100");
	Polinomial P4("-1.45 100 -56 120");
	EXPECT_EQ(P1 * 10, P3);
	EXPECT_EQ(P2, P4 * (-1));
	EXPECT_EQ(P1 + P1, P1 * 2);
	EXPECT_EQ(P2 + P2 + P2, P2 * 3);
}

TEST(TestNameMultiplicationOfPolinomials, TestNameOperators6) {
	Polinomial P1("5 120 6 314");
	Polinomial P2("1.5 100 5 120 3 123");
	Polinomial P3("7.5 220 25 240 15 243 9 414 30 434 18 437");
	Polinomial P4("12 999");
	EXPECT_EQ(P1 * P2, P3);
	EXPECT_ANY_THROW({
		P4 = P4 * P1;
		});
}

TEST(TestNamePolinomialInput, TestNameOperatorsa7) {
	Polinomial P1("5 120 6 314");
	Polinomial P2("1.5 100 5 120 3 123");
	string s3 = "5 120 6 314", s4 = "1.5 100 5 120 3 123";
	istringstream stream3(s3);
	istringstream stream4(s4);
	Polinomial P3;
	Polinomial P4;
	stream3 >> P3;
	stream4 >> P4;
	EXPECT_EQ(P1, P3);
	EXPECT_EQ(P2, P4);
}