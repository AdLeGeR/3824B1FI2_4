#include "pch.h"
#include "../Lab1Code/Polynom.h"

//Tests Forward_list_with_f_head:

TEST(Test_Forward_list_with_f_head, CreateDefaultEmptyListIsCorrectNoThrow)
{
    EXPECT_NO_THROW
    ({
        Forward_list_with_f_head list;
        EXPECT_TRUE(list.is_empty());
        });
}

TEST(Test_Forward_list_with_f_head, PushFrontIsCorrectNoThrow)
{
    Forward_list_with_f_head list;
    std::vector<std::pair<double, size_t>> data;

    EXPECT_NO_THROW
    ({
        for (size_t i = 1; i <  999; ++i)
        {
            list.push_front(10.0, i);
            data = list.get_list();
            EXPECT_EQ(data[0].second, i);
            EXPECT_DOUBLE_EQ(data[0].first, 10.0);
        }
        EXPECT_FALSE(list.is_empty());

        list.push_front(76.89, 0);
        data = list.get_list();
        EXPECT_EQ(data[0].second, 0);
        EXPECT_DOUBLE_EQ(data[0].first, 76.89);
        EXPECT_FALSE(list.is_empty());

        list.push_front(-45.8, 999);
        data = list.get_list();
        EXPECT_EQ(data[0].second, 999);
        EXPECT_DOUBLE_EQ(data[0].first, -45.8);
        EXPECT_FALSE(list.is_empty());

        EXPECT_EQ(data.size(), 1000);
        });
}

TEST(Test_Forward_list_with_f_head, CreateListByCopyingIsCorrectNoThrow)
{
    std::vector<std::pair<double, size_t>> data1, data2;
    EXPECT_NO_THROW
    ({
        Forward_list_with_f_head list1;
        EXPECT_TRUE(list1.is_empty());
        list1.push_front(34.0, 111);
        list1.push_front(-8.0, 654);
        EXPECT_FALSE(list1.is_empty());

        Forward_list_with_f_head list2(list1);
        EXPECT_FALSE(list2.is_empty());

        data1 = list1.get_list();
        data2 = list2.get_list();
        EXPECT_EQ(data1[0].second, data2[0].second);
        EXPECT_EQ(data1[1].second, data2[1].second);
        EXPECT_EQ(data1[0].first, data2[0].first);
        EXPECT_EQ(data1[1].first, data2[1].first);

        list2.clear();
        EXPECT_TRUE(list2.is_empty());
        });
}

TEST(Test_Forward_list_with_f_head, PushFrontAnyThrow)
{
    Forward_list_with_f_head list;

    EXPECT_THROW(list.push_front(0.0, 333), std::invalid_argument);

    EXPECT_THROW(list.push_front(76.89, -1), std::range_error); // -1 преобразуется в большое число, так как size_t.

    EXPECT_THROW(list.push_front(-45.8, 1000), std::range_error);

}

TEST(Test_Forward_list_with_f_head, AssignmentIsCorrectNoThrow)
{
    Forward_list_with_f_head list1, list2;
    std::vector<std::pair<double, size_t>> data1, data2;

    EXPECT_NO_THROW
    ({
        list1.push_front(23.1, 123);
        EXPECT_FALSE(list1.is_empty());
        EXPECT_TRUE(list2.is_empty());

        list2 = list1;
        EXPECT_FALSE(list1.is_empty());
        EXPECT_FALSE(list2.is_empty());

        data1 = list1.get_list();
        data2 = list2.get_list();
        EXPECT_EQ(data1[0].second, data2[0].second);
        EXPECT_EQ(data1[0].first, data2[0].first);
        });
}

TEST(Test_Forward_list_with_f_head, SortNoThrow)
{
    Forward_list_with_f_head list;
    std::vector<std::pair<double, size_t>> data;

    EXPECT_NO_THROW
    ({
        list.push_front(1.0, 111);
        list.push_front(2.0, 111);
        list.push_front(5.8, 1);
        list.push_front(-6.32, 256);
        list.push_front(67.0, 328);
        list.push_front(-35.0, 279);

        list.sort();

        data = list.get_list();
        EXPECT_EQ(data[0].second, 328);
        EXPECT_EQ(data[1].second, 279);
        EXPECT_EQ(data[2].second, 256);
        EXPECT_EQ(data[3].second, 111);
        EXPECT_EQ(data[4].second, 1);

        EXPECT_EQ(data[0].first, 67.0);
        EXPECT_EQ(data[1].first, -35.0);
        EXPECT_EQ(data[2].first, -6.32);
        EXPECT_EQ(data[3].first, 3.0);
        EXPECT_EQ(data[4].first, 5.8);
        });
}

//Tests Polynomial:

TEST(Test_Polynomial, CreateDefaultEmptyPolynomIsCorrectNoThrow)
{
    EXPECT_NO_THROW
    ({
        Polynomial p;
        EXPECT_TRUE(p.is_empty());
        });
}

TEST(Test_Polynomial, CreateNotEmptyPolynomIsCorrectNoThrow)
{
    std::vector<std::pair<double, size_t>> source1 = { { 1.0, 111 }, { 0.0, 245 }, { 15.0, 645 } }; // Моном с коэффциентом 0 игнорируется.
    std::vector<std::pair<double, size_t>> data1, data2;
    EXPECT_NO_THROW
    ({
        Polynomial p1(source1); // 15x^6y^4z^5 + 1x^1y^1z^1.
        EXPECT_FALSE(p1.is_empty());
        data1 = p1.get_polynom();
        EXPECT_EQ(data1[0].second, 645);
        EXPECT_EQ(data1[1].second, 111);
        EXPECT_EQ(data1[0].first, 15.0);
        EXPECT_EQ(data1[1].first, 1.0);
        //p1.print_polynom();

        Polynomial p2(p1); // 15x^6y^4z^5 + 1x^1y^1z^1.
        EXPECT_FALSE(p2.is_empty());
        data2 = p2.get_polynom();
        EXPECT_EQ(data2[0].second, data1[0].second);
        EXPECT_EQ(data2[1].second, data1[1].second);
        EXPECT_EQ(data2[0].first, data1[0].first);
        EXPECT_EQ(data2[1].first, data1[1].first);
        //p2.print_polynom();
        });
}

TEST(Test_Polynomial, CreateNotEmptyPolynomIsCorrectAnyThrow)
{
    std::vector<std::pair<double, size_t>> source1 = { { 1.0, -1 }}; // Степень монома меньше 0 не допустима.
    EXPECT_THROW(Polynomial p1(source1), std::range_error);

    std::vector<std::pair<double, size_t>> source2 = { { 1.0, 1000 } }; // Степень монома больше 999 не допустима.
    EXPECT_THROW(Polynomial p2(source2), std::range_error);
}

TEST(Test_Polynomial, AssignmentIsCorrectNoThrow)
{
    std::vector<std::pair<double, size_t>> source1 = { { 1.0, 100 }, { 2.0, 10 }, { 3.0, 1 } };
    std::vector<std::pair<double, size_t>> data1, data2;
    EXPECT_NO_THROW
    ({
        Polynomial p1(source1); // 1x^1 + 2y^1 + 3z^1.
        EXPECT_FALSE(p1.is_empty());
        data1 = p1.get_polynom();
        //p1.print_polynom();

        Polynomial p2;
        p2 = p1; // 1x^1 + 2y^1 + 3z^1.
        EXPECT_FALSE(p2.is_empty());
        data2 = p2.get_polynom();
        EXPECT_EQ(data2[0].second, data1[0].second);
        EXPECT_EQ(data2[1].second, data1[1].second);
        EXPECT_EQ(data2[2].second, data1[2].second);
        EXPECT_EQ(data2[0].first, data1[0].first);
        EXPECT_EQ(data2[1].first, data1[1].first);
        EXPECT_EQ(data2[2].first, data1[2].first);
        //p2.print_polynom();
        });
}

TEST(Test_Polynomial, PolynomAdditionAndSubtractionIsCorrectNoThrow)
{
    std::vector<std::pair<double, size_t>> source1 = { { 2.0, 200 }, { 3.0, 110 }, { 1.0, 1 } };

    std::vector<std::pair<double, size_t>> source2 = { { 1.0, 200 }, { -3.0, 110 }, { 4.0, 0 } };

    Polynomial p1(source1); // 2x^2 + 3x^1y^1 + 1z^1.
    //p1.print_polynom();
    Polynomial p2(source2); // 1x^2 - 3x^1y^1 + 4.
    //p2.print_polynom();

    std::vector<std::pair<double, size_t>> data1, data2;
    data1 = p1.get_polynom();
    data2 = p2.get_polynom();

    EXPECT_NO_THROW
    ({
        Polynomial add_p_1 = p1 + p2; // 3x^2 + 1z^1 +  4.
        //add_p_1.print_polynom();
        Polynomial sub_p_1 = p1 - p2; // 1x^2 + 6x^1y^1 + 1z^1 - 4.
        //sub_p_1.print_polynom();

        EXPECT_FALSE(add_p_1.is_empty());
        EXPECT_FALSE(sub_p_1.is_empty());

        data1 = add_p_1.get_polynom();
        EXPECT_EQ(data1[0].first, 3.0);
        EXPECT_EQ(data1[1].first, 1.0);
        EXPECT_EQ(data1[2].first, 4.0);
        EXPECT_EQ(data1[0].second, 200);
        EXPECT_EQ(data1[1].second, 1);
        EXPECT_EQ(data1[2].second, 0);

        data2 = sub_p_1.get_polynom();
        EXPECT_EQ(data2[0].first, 1.0);
        EXPECT_EQ(data2[1].first, 6.0);
        EXPECT_EQ(data2[2].first, 1.0);
        EXPECT_EQ(data2[3].first, -4.0);
        EXPECT_EQ(data2[0].second, 200);
        EXPECT_EQ(data2[1].second, 110);
        EXPECT_EQ(data2[2].second, 1);
        EXPECT_EQ(data2[3].second, 0);


        Polynomial add_p_2 = p2 + p1; // 3x^2 + 1z^1 +  4.
        //add_p_2.print_polynom();
        Polynomial sub_p_2 = p2 - p1; // -1x^2 - 6x^1y^1 - 1z^1 + 4.
        //sub_p_2.print_polynom();

        EXPECT_FALSE(add_p_2.is_empty());
        EXPECT_FALSE(sub_p_2.is_empty());

        data1 = add_p_2.get_polynom();
        EXPECT_EQ(data1[0].first, 3.0);
        EXPECT_EQ(data1[1].first, 1.0);
        EXPECT_EQ(data1[2].first, 4.0);
        EXPECT_EQ(data1[0].second, 200);
        EXPECT_EQ(data1[1].second, 1);
        EXPECT_EQ(data1[2].second, 0);

        data2 = sub_p_2.get_polynom();
        EXPECT_EQ(data2[0].first, -1.0);
        EXPECT_EQ(data2[1].first, -6.0);
        EXPECT_EQ(data2[2].first, -1.0);
        EXPECT_EQ(data2[3].first, 4.0);
        EXPECT_EQ(data2[0].second, 200);
        EXPECT_EQ(data2[1].second, 110);
        EXPECT_EQ(data2[2].second, 1);
        EXPECT_EQ(data2[3].second, 0);
        });
}

TEST(Test_Polynomial, PolynomMultiplicationConstantIsCorrectNoThrow)
{
    std::vector<std::pair<double, size_t>> source = { { 2.0, 200 }, { -3.0, 10 } };

    Polynomial p(source); // 2x^2 - 3y^1.
    //p.print_polynom();
    double const_p = 2.0;

    std::vector<std::pair<double, size_t>> data1, data2;
    data1 = p.get_polynom();

    EXPECT_NO_THROW
    ({
        Polynomial res_p = p * const_p; // 4x^2 - 6y^1, при const_p = 2.0.
        //res_p.print_polynom();
        EXPECT_FALSE(res_p.is_empty());

        data2 = res_p.get_polynom();
        EXPECT_EQ(data2[0].first, data1[0].first * const_p);
        EXPECT_EQ(data2[1].first, data1[1].first * const_p);
        EXPECT_EQ(data2[0].second, data1[0].second);
        EXPECT_EQ(data2[1].second, data1[1].second);
        });
}

TEST(Test_Polynomial, PolynomMultiplicationZeroNoThrow)
{
    std::vector<std::pair<double, size_t>> source = { { 2.0, 200 } };

    Polynomial p(source); // 2x^2.
    //p.print_polynom();

    EXPECT_NO_THROW
    ({
        Polynomial res_p = p * 0.0; // Empty.
        //res_p.print_polynom();
        EXPECT_TRUE(res_p.is_empty());
        });
}

TEST(Test_Polynomial, MultiplicationPolynomIsCorrectNoThrow)
{
    std::vector<std::pair<double, size_t>> source1 = { { 2.0, 100 }, { 1.0, 1 } };

    std::vector<std::pair<double, size_t>> source2 = { { 3.0, 100 }, { 4.0, 0 } };

    Polynomial p1(source1); // 2x^1 + 1z^1.
    //p1.print_polynom();
    Polynomial p2(source2); // 3x^1 + 4.
    //p2.print_polynom();

    std::vector<std::pair<double, size_t>> data;

    EXPECT_NO_THROW
    ({
        Polynomial res_p = p1 * p2; // 6x^2 + 3x^1z^1 + 8x^1 + 4z^1.
        //res_p.print_polynom();
        EXPECT_FALSE(res_p.is_empty());

        data = res_p.get_polynom();
        EXPECT_EQ(data[0].first, 6.0);
        EXPECT_EQ(data[1].first, 3.0);
        EXPECT_EQ(data[2].first, 8.0);
        EXPECT_EQ(data[3].first, 4.0);
        EXPECT_EQ(data[0].second, 200);
        EXPECT_EQ(data[1].second, 101);
        EXPECT_EQ(data[2].second, 100);
        EXPECT_EQ(data[3].second, 1);
        });
}

TEST(Test_Polynomial, MultiplicationPolynomAnyThrow)
{
    std::vector<std::pair<double, size_t>> source1 = { { 2.0, 999 } };

    std::vector<std::pair<double, size_t>> source2 = { { 4.0, 998 } };

    Polynomial p1(source1); // 2x^9y^9z^9.
    //p1.print_polynom();
    Polynomial p2(source2); // 4x^9y^9z^8.
    //p2.print_polynom();

    EXPECT_THROW(Polynomial res_p = p1 * p2, std::range_error);
}