#include "pch.h"
#include "../Project1/Header.h"

TEST(test_forward_list, test0) {
	F_List<int> list;

	list.push_front(1);
	list.push_front(2); //2 1 
	EXPECT_EQ(list.get_size(), 2);
	EXPECT_EQ(list[0], 2);
	EXPECT_EQ(list[1], 1);

	EXPECT_THROW({ list[-1]; }, std::out_of_range);
	EXPECT_THROW({ list[2]; }, std::out_of_range);


	list.clear();
	EXPECT_EQ(list.get_size(), 0);
	EXPECT_TRUE(list.empty());
	EXPECT_THROW({ list[1]; }, std::out_of_range);
	list.pop_front(); //исключения не возникает

	list.push_back(56);
	list.push_back(1);
	list.push_back(13);
	EXPECT_EQ(list[0], 56); //56 1 13 
	EXPECT_EQ(list[1], 1);
	EXPECT_EQ(list[2], 13);
	EXPECT_FALSE(list.empty());

	list.pop_front(); // 1 13 
	EXPECT_EQ(list.get_size(), 2);
	EXPECT_EQ(list[0], 1);
	EXPECT_EQ(list[1], 13);
}

TEST(test_forward_list, test_constructor_copy) {
	F_List<int> list1;
	list1.push_front(1);
	list1.push_front(2);
	list1.push_front(3); //3 2 1
	F_List<int> list2(list1);
	EXPECT_EQ(list2.get_size(), 3);
	EXPECT_EQ(list2[0], 3);
	EXPECT_EQ(list2[1], 2);
	EXPECT_EQ(list2[2], 1);
}

TEST(test_forward_list, test_constructor_copy_1) {
	F_List<int> list1;
	F_List<int> list2(list1);
	EXPECT_EQ(list2.get_size(), 0);
}

TEST(test_forward_list, test_operator_equal) {
	F_List<int> list1;
	list1.push_front(1);
	list1.push_front(2);
	F_List<int> list2;
	list2 = list1;
	EXPECT_EQ(list2.get_size(), 2);
	EXPECT_EQ(list2[0], 2);
	EXPECT_EQ(list2[1], 1);
}

TEST(test_forward_list, test_operator_equal1) {
	F_List<int> list1;
	list1.push_front(1);
	list1.push_front(2);
	F_List<int> list2;
	list2.push_front(123);
	F_List<int> list3;
	list1 = list2 = list3;
	EXPECT_EQ(list2.get_size(), 0);
	EXPECT_EQ(list1.get_size(), 0);
}

TEST(test_forward_list, test_operator_equal2) {
	F_List<int> list1;
	list1.push_back(2);
	list1.push_back(34);
	list1 = list1;
	EXPECT_EQ(list1.get_size(), 2);
	EXPECT_EQ(list1[0], 2);
	EXPECT_EQ(list1[1], 34);
}
TEST(test_forward_list, test_insert) {

	F_List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);

	list.insert(234, 2);
	EXPECT_EQ(list.get_size(), 5);
	EXPECT_EQ(list[2], 234);

	EXPECT_THROW({ list.insert(245,-1); }, std::out_of_range);
	EXPECT_THROW({ list.insert(12,5); }, std::out_of_range);
}


void check_correct(Polinom& pol, std::string& polinom) {
	std::ostringstream out;
	out << pol;
	EXPECT_EQ(out.str(), polinom);
}

TEST(test_polinom0, test_constructor) {
	std::vector<unsigned int> deg = { 100, 456,20 };
	std::vector<double> coeff = { 1,4,5 };
	Polinom pol(coeff, deg);

	std::vector<unsigned int> deg1 = { 1001, 456,20 };
	std::vector<double> coeff1 = { 1,4,5 };
	EXPECT_THROW({ Polinom pol1(coeff1,deg1); }, std::invalid_argument);


	std::vector<unsigned int> deg2 = { 456,20 };
	std::vector<double> coeff2 = { 1,4,5 };
	EXPECT_THROW({ Polinom pol2(coeff2,deg2); }, std::invalid_argument);

	std::ostringstream out;
	out << pol;
	std::string polinom = "4x4y5z6 + x1y0z0 + 5x0y2z0";
	EXPECT_EQ(out.str(), polinom);
}

TEST(test_polinom0, test_constructor1) {
	Polinom pol;
	EXPECT_EQ(pol.count_monom(), 0);
}
TEST(test_polinom0, test_constructor2) {
	std::vector<double>coeff = { 1,2,2 };
	std::vector<unsigned int> deg = { 111,123, 123 };
	Polinom pol(coeff, deg);
	std::string polinom = "4x1y2z3 + x1y1z1";
	check_correct(pol, polinom);
}
TEST(test_polinom0, test_constructor3) {
	std::vector<unsigned int> deg = { 111, 456, 123, 123, 456, 789, 456, 789, 789, 888 };
	std::vector<double>coeff = { 1, 4, 2, 3, 4, 8, 4, 1, 1, 2 };
	Polinom pol(coeff, deg);
	std::string polinom = "2x8y8z8 + 10x7y8z9 + 12x4y5z6 + 5x1y2z3 + x1y1z1";
	check_correct(pol, polinom);
}

//////////////////////
TEST(test_polinom0, test_add_monom) {
	Polinom pol;
	pol.add_monom(2.5, 678);
	pol.add_monom(3, 10);

	std::string polinom = "2.5x6y7z8 + 3x0y1z0";
	check_correct(pol, polinom);

}
TEST(test_polinom0, test_add_monom1) {
	std::vector<double> coeff = { 1,23,45.67 };
	std::vector<unsigned int> degree = { 789, 11, 100 };
	Polinom pol(coeff, degree);
	pol.add_monom(-7, 101);

	std::string polinom = "x7y8z9 - 7x1y0z1 + 45.67x1y0z0 + 23x0y1z1";
	check_correct(pol, polinom);
}
TEST(test_polinom0, test_add_monom2) {
	std::vector<double> coeff = { 1,23,45.67 };
	std::vector<unsigned int> degree = { 789, 11, 100 };
	Polinom pol(coeff, degree);
	pol.add_monom(-7, 809);

	std::string polinom = "-7x8y0z9 + x7y8z9 + 45.67x1y0z0 + 23x0y1z1";
	check_correct(pol, polinom);
}

TEST(test_polinom0, test_add_monom3) {
	Polinom pol;
	pol.add_monom(3, 101);
	pol.add_monom(3, 101);
	std::string polinom = "6x1y0z1";
	check_correct(pol, polinom);
}
TEST(test_polinom0, test_add_monom4) {
	std::vector<double> coeff = { 1,23,45.67 };
	std::vector<unsigned int> degree = { 789, 11, 100 };
	Polinom pol(coeff, degree);
	pol.add_monom(-4, 789);
	pol.add_monom(11, 11);
	pol.add_monom(6, 99);
	std::string polinom = "-3x7y8z9 + 45.67x1y0z0 + 6x0y9z9 + 34x0y1z1";
	check_correct(pol, polinom);
}
/////////////////
TEST(test_polinom0, test_costructor_copy) {
	std::vector<double> coeff = { 1,23,45.67 };
	std::vector<unsigned int> degree = { 789, 11, 100 };
	Polinom pol(coeff, degree);
	Polinom pol1(pol);

	std::string polinom = "x7y8z9 + 45.67x1y0z0 + 23x0y1z1";
	check_correct(pol1, polinom);
}
//////////////////
TEST(test_polinom0, test_operator_equal) {
	std::vector<double> coeff = { 1,23,45.67 };
	std::vector<unsigned int> degree = { 789, 11, 100 };
	Polinom pol(coeff, degree);

	Polinom pol1;
	pol1 = pol;

	std::string polinom = "x7y8z9 + 45.67x1y0z0 + 23x0y1z1";
	check_correct(pol1, polinom);
}
/////////////////
TEST(test_polinom1, test_multip_const) {
	std::vector<double> coeff = { 1,2,3 };
	std::vector<unsigned int> degree = { 123, 345, 789 };
	Polinom pol(coeff, degree);
	pol = pol * 4.5;

	std::string polinom = "13.5x7y8z9 + 9x3y4z5 + 4.5x1y2z3";
	check_correct(pol, polinom);

	Polinom pol2(pol);
	pol2 = 4.5 * pol;
	check_correct(pol, polinom);

}
TEST(test_polinom1, test_multip_const1) {
	Polinom pol;
	pol = pol * 12435.8;
	EXPECT_EQ(pol.count_monom(), 0);
}
TEST(test_polinom1, test_multip_const2) {
	std::vector<double> coeff = { 1,2,3 };
	std::vector<unsigned int> degree = { 123, 345, 789 };
	Polinom pol(coeff, degree);
	pol = pol * 0;
	EXPECT_EQ(pol.count_monom(), 0);
}

/////////////////
TEST(test_polinom1, test_operator_sum) {
	std::vector<double> coeff = { 3,4,99 };
	std::vector<unsigned int> degr = { 771,556,101 };
	Polinom pol(coeff, degr);

	std::vector<double> coeff1 = { 2,8 };
	std::vector<unsigned int> degr1 = { 556, 771 };
	Polinom pol1(coeff1, degr1);

	Polinom pol2;
	pol2 = pol + pol1;

	std::string polinom = "11x7y7z1 + 6x5y5z6 + 99x1y0z1";
	check_correct(pol2, polinom);
}

TEST(test_polinom1, test_operator_sum1) { //исчезновение монома "123"
	std::vector<double> coeff = { -1,1,5 };
	std::vector<unsigned int> degr = { 123, 234, 456 };
	Polinom pol(coeff, degr);

	std::vector<double> coeff1 = { 1, 4 };
	std::vector<unsigned int> degr1 = { 123, 456 };
	Polinom pol1(coeff1, degr1);

	Polinom pol2;
	pol2 = pol + pol1;

	std::string polinom = "9x4y5z6 + x2y3z4";
	check_correct(pol2, polinom);
	EXPECT_EQ(pol2.count_monom(), 2); //число мономов: 2
}

TEST(test_polinom1, test_operator_sum2) {
	std::vector<double> coeff = { -1, -4 };
	std::vector<unsigned int> degr = { 123, 456 };
	Polinom pol(coeff, degr);

	std::vector<double> coeff1 = { 1, 4 };
	std::vector<unsigned int> degr1 = { 123, 456 };
	Polinom pol1(coeff1, degr1);

	Polinom pol2;
	pol2 = pol + pol1;

	std::string polinom = "";
	check_correct(pol2, polinom);
	EXPECT_EQ(pol2.count_monom(), 0);
}
TEST(test_polinom1, test_operator_sum3) {
	Polinom pol;
	Polinom pol1;
	pol1.add_monom(3, 123);
	pol1.add_monom(4, 345);

	Polinom pol2 = pol + pol1;
	std::string polinom = "4x3y4z5 + 3x1y2z3";
	check_correct(pol2, polinom);
}
///////////////////
TEST(test_polinom1, test_operator_diff) {
	std::vector<double> coeff = { 1, 4 };
	std::vector<unsigned int> degr = { 123, 456 };
	Polinom pol(coeff, degr);

	std::vector<double> coeff1 = { 1, 4 };
	std::vector<unsigned int> degr1 = { 123, 456 };
	Polinom pol1(coeff1, degr1);

	Polinom pol2 = pol - pol1;


	std::string polinom = "";
	check_correct(pol2, polinom);
	EXPECT_EQ(pol2.count_monom(), 0);
}
TEST(test_polinom1, test_operator_diff1) {
	Polinom pol;
	pol.add_monom(2, 123);

	Polinom pol1;
	pol1.add_monom(3, 234);
	pol1.add_monom(4, 100);

	Polinom pol2 = pol - pol1;
	std::string polinom = "-3x2y3z4 + 2x1y2z3 - 4x1y0z0";
	check_correct(pol2, polinom);

	Polinom pol3 = pol + pol1 * (-1);
	check_correct(pol3, polinom);

	Polinom pol4 = pol + (-1) * pol1;
	check_correct(pol4, polinom);
}
///////////////////////
TEST(test_polinom1, test_operator_muptip_polinom) {

	std::vector<unsigned int> deg = { 111, 222 };
	std::vector<double> coeff = { 1,2 };
	Polinom pol(coeff, deg);

	std::vector<unsigned int> deg1 = { 333,222 };
	std::vector<double> coeff1 = { 1,2 };
	Polinom pol1(coeff1, deg1);

	Polinom pol2;
	pol2 = pol * pol1;

	std::string polinom = "2x5y5z5 + 5x4y4z4 + 2x3y3z3";
	check_correct(pol2, polinom);

}
TEST(test_polinom1, test_operator_multip_polinom1) {
	std::vector<unsigned int> deg = { 111, 222, 444 };
	std::vector<double> coeff = { 1,2, 3 };
	Polinom pol(coeff, deg);

	std::vector<unsigned int> deg1 = { 0 };
	std::vector<double> coeff1 = { 1 };
	Polinom pol1(coeff1, deg1);

	Polinom pol2;
	pol2 = pol * pol1;

	std::string polinom = "3x4y4z4 + 2x2y2z2 + x1y1z1";
	check_correct(pol2, polinom);
}
TEST(test_polinom1, test_operator_multip_polinom2) {
	std::vector<unsigned int> deg = { 999 };
	std::vector<double> coeff = { 1 };
	Polinom pol(coeff, deg);

	std::vector<unsigned int> deg1 = { 444 };
	std::vector<double> coeff1 = { 1 };
	Polinom pol1(coeff1, deg1);

	Polinom pol2;
	EXPECT_THROW({ pol2 = pol * pol1; }, std::runtime_error);
}
TEST(test_polinom1, test_operator_multip_polinom3) {
	std::vector<unsigned int> deg = { 10, 457, 613, 776 };
	std::vector<double> coeff = { 1,2, 3,4 };
	Polinom pol(coeff, deg);

	std::vector<unsigned int> deg1 = { 111,222 };
	std::vector<double> coeff1 = { 7,9 };
	Polinom pol1(coeff1, deg1);

	Polinom pol2;
	pol2 = pol * pol1;

	std::string polinom = "36x9y9z8 + 28x8y8z7 + 27x8y3z5 + 21x7y2z4 + 18x6y7z9 + 14x5y6z8 + 9x2y3z2 + 7x1y2z1";
	check_correct(pol2, polinom);
}
TEST(test_polinom1, test_operator_multip_polinom4) {
	std::vector<unsigned int> deg = { 111, 222 };
	std::vector<double> coeff = { 1,1 };
	Polinom pol(coeff, deg);

	std::vector<unsigned int> deg1 = { 111,111 };
	std::vector<double> coeff1 = { -1, 1 };
	Polinom pol1(coeff1, deg1);

	Polinom pol2;
	pol2 = pol * pol1;

	std::string polinom = "";
	check_correct(pol2, polinom);
}
TEST(test_polinom1, test_operator_multip_polinom5) {
	Polinom pol;
	Polinom pol1;
	pol1.add_monom(3, 101);
	EXPECT_EQ(pol1.count_monom(), 1);
	Polinom pol2 = pol * pol1;
	EXPECT_EQ(pol2.count_monom(), 0);
}
//////////////////////////
TEST(test_polinom2, test_operator_output) {
	std::vector<unsigned int> deg = { 512, 123, 234 };
	std::vector<double> coeff = { -1, 2, 3 };
	Polinom pol(coeff, deg);

	std::vector<unsigned int> deg1 = { 0, 467 };
	std::vector<double> coeff1 = { 3,4 };
	Polinom pol1(coeff1, deg1);

	std::ostringstream out;
	out << pol << "\t" << pol1;
	std::string result = "-x5y1z2 + 3x2y3z4 + 2x1y2z3	4x4y6z7 + 3";
	EXPECT_EQ(out.str(), result);
}
//////////////////////////
TEST(test_polinom2, test_input) {
	Polinom pol;
	std::istringstream test("-1:156,2:467,3:111");
	test >> pol;
	std::string polinom = "2x4y6z7 - x1y5z6 + 3x1y1z1";
	check_correct(pol, polinom);
}
TEST(test_polinom2, test_input1) {
	Polinom pol;
	std::istringstream test("2 : 156, 3:345");
	EXPECT_THROW({ test >> pol; }, std::runtime_error); //пробел -  некорректный символ

	std::istringstream test1("2fg:156,3:345"); //некорректные символы
	EXPECT_THROW({ test1 >> pol; }, std::runtime_error);

	std::istringstream test2("2-1:156,3:345"); // - в некорректном месте
	EXPECT_THROW({ test2 >> pol; }, std::runtime_error);

	std::istringstream test3(":156"); //отсутствует коэффициент
	EXPECT_THROW({ test3 >> pol; }, std::runtime_error);

	std::istringstream test4("23.5:"); //отсутствует степень
	EXPECT_THROW({ test4 >> pol; }, std::runtime_error);

	std::istringstream test5("23.5.56:123"); //некорректное количество точек
	EXPECT_THROW({ test5 >> pol; }, std::runtime_error);

	std::istringstream test6("012:123"); //ноль в начале коэффициента
	EXPECT_THROW({ test6 >> pol; }, std::runtime_error);

	std::istringstream test7("12:g123"); //некорректная степень
	EXPECT_THROW({ test7 >> pol; }, std::runtime_error);

	std::istringstream test8("12:1234"); //некорректная степень (исключение бросается в конструкторе)
	EXPECT_THROW({ test8 >> pol; }, std::invalid_argument);
}
TEST(test_polinom2, test_input2) {
	Polinom pol;
	std::istringstream test("-12.4:888,6:652,8:111,23:11,0:101");
	test >> pol;
	std::string polinom = "-12.4x8y8z8 + 6x6y5z2 + 8x1y1z1 + 23x0y1z1";
	check_correct(pol, polinom);
}
TEST(test_polinom2, test_input3) {
	Polinom pol1;
	Polinom pol2;
	std::istringstream test("12:123,5.6:678\n5:134");
	test >> pol1 >> pol2;
	std::string polinom1 = "5.6x6y7z8 + 12x1y2z3";
	std::string polinom2 = "5x1y3z4";
	check_correct(pol1, polinom1);
	check_correct(pol2, polinom2);
}