#include <gtest/gtest.h>
#include "../lib_polynomial/polynomial.h"

TEST(Test_Polynomial, test_constructor1) {
	ASSERT_NO_THROW(Polynomial A);
}

TEST(Test_Polynomial, test_sum_numb) {
	EXPECT_EQ(sum_numb(123), 6);
	EXPECT_EQ(sum_numb(684), 18);
}

TEST(Test_Polynomial, test_record) {
	std::string test_input = "4\n2\n0\n0\n-9\n2\n3\n7\n6\n0\n0\n3\n0\n";

	auto original_cin = std::cin.rdbuf();
	std::istringstream fake_cin(test_input);
	std::cin.rdbuf(fake_cin.rdbuf());

	Polynomial A;
	A.record();
	std::cin.rdbuf(original_cin);

	List B;
	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{6, 3});
	B.push_back(std::pair<double, int>{4, 200});

	Polynomial C(B);

	EXPECT_EQ(A, C);
}

TEST(Test_Polynomial, test_summ) {
	Polynomial D;
	List B, A, C;
	A.push_back(std::pair<double, int>{-9, 237});
	A.push_back(std::pair<double, int>{6, 3});
	A.push_back(std::pair<double, int>{4, 200});


	C.push_back(std::pair<double, int>{5, 160});
	C.push_back(std::pair<double, int>{-6, 102});

	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{5, 160});
	B.push_back(std::pair<double, int>{-6, 102});
	B.push_back(std::pair<double, int>{6, 003});
	B.push_back(std::pair<double, int>{4, 200});

	Polynomial A1(A), C1(C);
	D = A1 + C1;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_sub) {
	Polynomial D;
	List B, A, C;
	A.push_back(std::pair<double, int>{-9, 237});
	A.push_back(std::pair<double, int>{6, 3});
	A.push_back(std::pair<double, int>{4, 200});


	C.push_back(std::pair<double, int>{5, 160});
	C.push_back(std::pair<double, int>{-6, 102});

	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{-5, 160});
	B.push_back(std::pair<double, int>{+6, 102});
	B.push_back(std::pair<double, int>{6, 003});
	B.push_back(std::pair<double, int>{4, 200});

	Polynomial A1(A), C1(C);
	D = A1 - C1;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_mul_const) {
	Polynomial D;
	List B, A;
	A.push_back(std::pair<double, int>{-9, 237});
	A.push_back(std::pair<double, int>{6, 3});
	A.push_back(std::pair<double, int>{4, 200});

	B.push_back(std::pair<double, int>{27, 237});
	B.push_back(std::pair<double, int>{-18, 003});
	B.push_back(std::pair<double, int>{-12, 200});
	Polynomial A1(A);

	D = (-3) * A1;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_mul) {
	Polynomial D;
	List B, A, C;
	A.push_back(std::pair<double, int>{-9, 235});
	A.push_back(std::pair<double, int>{6, 3});
	A.push_back(std::pair<double, int>{4, 200});

	C.push_back(std::pair<double, int>{5, 140});
	C.push_back(std::pair<double, int>{-6, 102});

	B.push_back(std::pair<double, int>{-45, 375});
	B.push_back(std::pair<double, int>{54, 337});
	B.push_back(std::pair<double, int>{+30, 143});
	B.push_back(std::pair<double, int>{20, 340});
	B.push_back(std::pair<double, int>{-36, 105});
	B.push_back(std::pair<double, int>{-24, 302});

	Polynomial A1(A), C1(C);
	D = A1 * C1;
	Polynomial D1(B);
	EXPECT_EQ(D, D1);
}

TEST(Test_Polynomial, test_rav) {
	Polynomial C;
	List B, A;
	A.push_back(std::pair<double, int>{-9, 237});
	A.push_back(std::pair<double, int>{6, 3});
	A.push_back(std::pair<double, int>{4, 200});

	B.push_back(std::pair<double, int>{-9, 237});
	B.push_back(std::pair<double, int>{6, 003});
	B.push_back(std::pair<double, int>{4, 200});

	Polynomial A1(A);
	C = A;
	Polynomial D(B);
	EXPECT_EQ(D, C);
}

TEST(Test_Polynomial, test_overflou) {
	List A, C;
	A.push_back(std::pair<double, int>{-9, 235});
	C.push_back(std::pair<double, int>{-6, 107});
	Polynomial A1(A), C1(C);
	ASSERT_ANY_THROW(A1 * C1);
}

TEST(Test_Polynomial, test_mul_zero_coef) {
	List A, B, C;
	A.push_back(std::pair<double, int>{0, 100});
	A.push_back(std::pair<double, int>{5, 50});

	B.push_back(std::pair<double, int>{3, 20});
	B.push_back(std::pair<double, int>{0, 10});


	C.push_back(std::pair<double, int>{15, 70});

	Polynomial A1(A), B1(B), C1(C);
	Polynomial D = A1 * B1;
	EXPECT_EQ(D, C1);
}

TEST(Test_Polynomial, test_mul_overflow_x) {
	List A, B;
	A.push_back(std::pair<double, int>{1, 900});
	B.push_back(std::pair<double, int>{1, 100});

	Polynomial A1(A), B1(B);
	ASSERT_ANY_THROW(A1 * B1);
}

TEST(Test_Polynomial, test_mul_const_zero) {
	List A, B;
	A.push_back(std::pair<double, int>{5, 123});
	A.push_back(std::pair<double, int>{-3, 456});

	Polynomial A1(A);
	Polynomial D = 0 * A1;
	Polynomial E;
	EXPECT_EQ(D, E);
}


TEST(Test_Polynomial, test_combined_operations) {
	List A, B, C;
	A.push_back(std::pair<double, int>{2, 100});
	B.push_back(std::pair<double, int>{3, 100});
	C.push_back(std::pair<double, int>{4, 100});

	Polynomial A1(A), B1(B), C1(C);
	Polynomial D = ((A1 + B1) * 2) - C1;

	List G;
	G.push_back(std::pair<double, int>{6, 100});
	Polynomial G1(G);
	EXPECT_EQ(D, G1);
}

//Пользователь никак не может ввести пустой полином поэтому тестов на операции с ними нет