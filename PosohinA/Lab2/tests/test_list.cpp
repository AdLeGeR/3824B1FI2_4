#include <gtest/gtest.h>
#include "../lib_list/list.h"

TEST(Test_List, test_constructor1) {
	ASSERT_NO_THROW(List A);
}

TEST(Test_List, test_is_empty1) {
	List A;
	EXPECT_TRUE(A.is_empty());
}

TEST(Test_List, test_is_empty2) {
	List A;
	A.push_front(std::pair<double, int>(1.0, 1));
	EXPECT_FALSE(A.is_empty());
}

TEST(Test_List, test_copy1) {
	List A;
	A.push_front(std::pair<double, int>(1.0, 1));
	A.push_front(std::pair<double, int>(2.0, 2));
	A.push_front(std::pair<double, int>(3.0, 3));
	ASSERT_NO_THROW(List B(A));
}

TEST(Test_List, test_copy2) {
	List A;
	A.push_front(std::pair<double, int>(1.0, 1));
	A.push_front(std::pair<double, int>(2.0, 2));
	A.push_front(std::pair<double, int>(3.0, 3));
	List B(A);
	auto it1 = A.begin();
	auto it2 = B.begin();
	while (it1 != A.end() && it2 != B.end()) {
		EXPECT_EQ((*it1).first, (*it2).first);
		EXPECT_EQ((*it1).second, (*it2).second);
		it1++;
		it2++;
	}
}

TEST(Test_List, test_copy3) {
	List A;
	ASSERT_NO_THROW(List B(A));
}

TEST(Test_List, test_pop_front1) {
	List A;
	A.push_back(std::pair<double, int>(1.0, 1));
	ASSERT_NO_THROW(A.pop_front());
}

TEST(Test_List, test_pop_front2) {
	List A;
	ASSERT_ANY_THROW(A.pop_front());
}

TEST(Test_List, test_pop_front3) {
	List A;
	A.push_front(std::pair<double, int>(1.0, 1));
	A.push_front(std::pair<double, int>(2.0, 2));
	A.push_front(std::pair<double, int>(3.0, 3));
	A.pop_front();
	auto it = A.begin();
	std::pair<double, int> ot = { 2.0, 2 };
	EXPECT_EQ((*it).first, ot.first);
	EXPECT_EQ((*it).second, ot.second);

}

TEST(Test_List, test_pop_front4) {
	List A;
	A.push_back(std::pair<double, int>(1.0, 1));
	A.pop_front();
	EXPECT_TRUE(A.is_empty());
}

TEST(Test_List, test_pop_back1) {
	List A;
	A.push_back(std::pair<double, int>(1.0, 1));
	ASSERT_NO_THROW(A.pop_back());
}

TEST(Test_List, test_pop_back2) {
	List A;
	ASSERT_ANY_THROW(A.pop_back());
}

TEST(Test_List, test_pop_back3) {
	List A;
	A.push_back(std::pair<double, int>(1.0, 1));
	A.pop_back();
	EXPECT_TRUE(A.is_empty());
}

TEST(Test_List, test_push_front1) {
	List A;
	ASSERT_NO_THROW(A.push_front(std::pair<double, int>(1.0, 1)));
}

TEST(Test_List, test_push_front2) {
	List A;
	A.push_front(std::pair<double, int>(1.0, 1));
	ASSERT_NO_THROW(A.push_front(std::pair<double, int>(1.0, 1)));
}

TEST(Test_List, test_push_front3) {
	List A;
	A.push_front(std::pair<double, int>(1.0, 3));
	A.push_front(std::pair<double, int>(2.0, 2));
	A.push_front(std::pair<double, int>(3.0, 1));
	auto it1 = A.begin();
	int i = 1;
	while (it1 != A.end()) {
		EXPECT_EQ((*it1).second, i);
		i++;
		it1++;
	}
}

TEST(Test_List, test_push_back1) {
	List A;
	ASSERT_NO_THROW(A.push_back(std::pair<double, int>(1.0, 1)));
}

TEST(Test_List, test_push_back2) {
	List A;
	A.push_back(std::pair<double, int>(1.0, 1));
	ASSERT_NO_THROW(A.push_back(std::pair<double, int>(1.0, 1)));
}

TEST(Test_List, test_push_back3) {
	List A;
	A.push_back(std::pair<double, int>(1.0, 1));
	A.push_back(std::pair<double, int>(2.0, 2));
	A.push_back(std::pair<double, int>(3.0, 3));
	auto it1 = A.begin();
	int i = 1;
	while (it1 != A.end()) {
		EXPECT_EQ((*it1).second, i);
		i++;
		it1++;
	}
}

TEST(Test_Ierator, test_read) {
	List A;
	A.push_front(std::pair<double, int>(1.0, 3));
	A.push_front(std::pair<double, int>(2.0, 2));
	A.push_front(std::pair<double, int>(3.0, 1));
	int i = 1;
	for (auto it = A.begin(); it != A.end(); it++) {
		EXPECT_EQ((*it).second, i);
		i++;
	}
}

TEST(Test_Ierator, test_ne_read) {
	List A;
	A.push_front(std::pair<double, int>(1.0, 1));
	A.push_front(std::pair<double, int>(2.0, 2));
	A.push_front(std::pair<double, int>(3.0, 3));
	List::Iterator it = A.begin();
	for (int i = 1; i < 4; i++) {
		(*it).second = i;
		it++;
	}
	List::Iterator ie = A.begin();
	for (int i = 1; i < 4; i++) {
		EXPECT_EQ((*ie).second, i);
		ie++;
	}
}

TEST(Test_Ierator, test_0) {
	List A;
	ASSERT_NO_THROW(List::Iterator it = A.begin());
}

TEST(Test_List, test_insert_middle) {
	List A;
	A.push_back(std::pair<double, int>(1.0, 1));
	A.push_back(std::pair<double, int>(3.0, 3));

	auto it = A.begin();
	Node* first = it.get_current();

	A.insert(first, std::pair<double, int>(2.0, 2));

	it = A.begin();
	EXPECT_DOUBLE_EQ((*it).first, 1.0);
	EXPECT_EQ((*it).second, 1);
	it++;
	EXPECT_DOUBLE_EQ((*it).first, 2.0);
	EXPECT_EQ((*it).second, 2);
	it++;
	EXPECT_DOUBLE_EQ((*it).first, 3.0);
	EXPECT_EQ((*it).second, 3);
}

TEST(Test_List, test_insert_empty_list) {
	List A;
	ASSERT_ANY_THROW(A.insert(nullptr, std::pair<double, int>(1.0, 1)));
}

TEST(Test_List, test_assignment_empty) {
	List A;
	A.push_back(std::pair<double, int>(1.0, 1));
	A.push_back(std::pair<double, int>(2.0, 2));

	List B;
	A = B;

	EXPECT_TRUE(A.is_empty());
}


TEST(Test_List, test_assignment_self) {
	List A;
	A.push_back(std::pair<double, int>(1.0, 1));
	A.push_back(std::pair<double, int>(2.0, 2));

	ASSERT_NO_THROW(A = A);

	auto it = A.begin();
	EXPECT_DOUBLE_EQ((*it).first, 1.0);
	it++;
	EXPECT_DOUBLE_EQ((*it).first, 2.0);
	EXPECT_EQ((*it).second, 2);
}


TEST(Test_List, test_clear_empty) {
	List A;
	ASSERT_NO_THROW(A.clear());
	EXPECT_TRUE(A.is_empty());
}


TEST(Test_List, test_pop_back_all_elements) {
	List A;
	A.push_back(std::pair<double, int>(1.0, 1));
	A.push_back(std::pair<double, int>(2.0, 2));

	A.pop_back();
	EXPECT_FALSE(A.is_empty());
	A.pop_back();
	EXPECT_TRUE(A.is_empty());
}