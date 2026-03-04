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

    EXPECT_NO_THROW
    ({
        for (size_t i = 1; i < 999; ++i)
        {
            list.push_front(10.0, i);
        }
        EXPECT_FALSE(list.is_empty());

        list.push_front(76.89, 0);
        EXPECT_FALSE(list.is_empty());

        list.push_front(-45.8, 999);
        EXPECT_FALSE(list.is_empty());
        });
}

TEST(Test_Forward_list_with_f_head, CreateListByCopyingIsCorrectNoThrow)
{
    EXPECT_NO_THROW
    ({
        Forward_list_with_f_head list1;
        EXPECT_TRUE(list1.is_empty());
        list1.push_front(34.0, 111);
        list1.push_front(-8.0, 654);
        EXPECT_FALSE(list1.is_empty());

        Forward_list_with_f_head list2(list1);
        EXPECT_FALSE(list2.is_empty());

        list2.clear();
        EXPECT_TRUE(list2.is_empty());
        });
}

TEST(Test_Forward_list_with_f_head, PushFrontAnyThrow)
{
    Forward_list_with_f_head list;

    EXPECT_THROW(list.push_front(0.0, 333), std::invalid_argument);

    EXPECT_THROW(list.push_front(76.89, -1), std::range_error);

    EXPECT_THROW(list.push_front(-45.8, 1000), std::range_error);

}

TEST(Test_Forward_list_with_f_head, AssignmentIsCorrectNoThrow)
{
    Forward_list_with_f_head list1, list2;

    EXPECT_NO_THROW
    ({
        list1.push_front(23.1, 123);
        EXPECT_FALSE(list1.is_empty());
        EXPECT_TRUE(list2.is_empty());

        list2 = list1;
        EXPECT_FALSE(list1.is_empty());
        EXPECT_FALSE(list2.is_empty());
        });
}

TEST(Test_Forward_list_with_f_head, SortNoThrow)
{
    Forward_list_with_f_head list;

    EXPECT_NO_THROW
    ({
        list.push_front(1.0, 111);
        list.push_front(2.0, 111);
        list.push_front(5.8, 1);
        list.push_front(-6.32, 256);
        list.push_front(67.0, 328);
        list.push_front(-35.0, 279);

        list.sort();
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
    EXPECT_NO_THROW
    ({
        Polynomial p1(source1); // 15x^6y^4z^5 + 1x^1y^1z^1.
        EXPECT_FALSE(p1.is_empty());
        //p1.print_polynom();

        Polynomial p2(p1); // 15x^6y^4z^5 + 1x^1y^1z^1.
        EXPECT_FALSE(p2.is_empty());
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
    
    EXPECT_NO_THROW
    ({
        Polynomial p1(source1); // 1x^1 + 2y^1 + 3z^1.
        EXPECT_FALSE(p1.is_empty());
        //p1.print_polynom();

        Polynomial p2;
        p2 = p1; // 1x^1 + 2y^1 + 3z^1.
        EXPECT_FALSE(p2.is_empty());
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

    EXPECT_NO_THROW
    ({
        Polynomial add_p_1 = p1 + p2; // 3x^2 + 1z^1 +  4.
        //add_p_1.print_polynom();
        Polynomial sub_p_1 = p1 - p2; // 1x^2 + 6x^1y^1 + 1z^1 - 4.
        //sub_p_1.print_polynom();

        EXPECT_FALSE(add_p_1.is_empty());
        EXPECT_FALSE(sub_p_1.is_empty());


        Polynomial add_p_2 = p2 + p1; // 3x^2 + 1z^1 +  4.
        //add_p_2.print_polynom();
        Polynomial sub_p_2 = p2 - p1; // -1x^2 - 6x^1y^1 - 1z^1 + 4.
        //sub_p_2.print_polynom();

        EXPECT_FALSE(add_p_2.is_empty());
        EXPECT_FALSE(sub_p_2.is_empty());
        });
}

TEST(Test_Polynomial, PolynomMultiplicationConstantIsCorrectNoThrow)
{
    std::vector<std::pair<double, size_t>> source = { { 2.0, 200 }, { -3.0, 10 } };

    Polynomial p(source); // 2x^2 - 3y^1.
    //p.print_polynom();
    double const_p = 2.0;

    EXPECT_NO_THROW
    ({
        Polynomial res_p = p * const_p; // 4x^2 - 6y^1, при const_p = 2.0.
        //res_p.print_polynom();
        EXPECT_FALSE(res_p.is_empty());
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

    EXPECT_NO_THROW
    ({
        Polynomial res_p = p1 * p2; // 6x^2 + 3x^1z^1 + 8x^1 + 4z^1.
        //res_p.print_polynom();
        EXPECT_FALSE(res_p.is_empty());
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