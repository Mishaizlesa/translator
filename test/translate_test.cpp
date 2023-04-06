#include "solve_expr.h"
#include <gtest/gtest.h>
#include <iostream>
class translate : 
    public ::testing::TestWithParam<int>{

protected:
    stdvector<polynome>a;

    polynome A, B, C, D;

    translate()
    {
        srand(40);
        const int K = 5;
        for (int i = 0; i < 5; ++i)
        {
            A.insert(monome(rand(), rand(), rand(), rand()));
            A.insert(monome(rand(), rand(), rand(), rand()));

            B.insert(monome(rand(), rand(), rand(), rand()));
            B.insert(monome(rand(), rand(), rand(), rand()));

            C.insert(monome(rand(), rand(), rand(), rand()));
            C.insert(monome(rand(), rand(), rand(), rand()));
            C.insert(monome(rand(), rand(), rand(), rand()));

            D.insert(monome(rand(), rand(), rand(), rand()));
        }

        a.push_back(A);
        a.push_back(B);
        a.push_back(C);
        a.push_back(D);
    }
    
};

INSTANTIATE_TEST_SUITE_P(trans4late, translate, ::testing::Values(-1, 0, 1));


TEST_P(translate, can_create_monome)
{
    EXPECT_NO_THROW(monome(GetParam(), 1, 1, 1));
}

TEST(test, can_create_polynome)
{
    EXPECT_NO_THROW(polynome());
}

TEST_F(translate, can_difx)
{
    EXPECT_NO_THROW(A.difx());
}
TEST_F(translate, can_dify)
{
    EXPECT_NO_THROW(A.dify());
}

TEST_F(translate, can_difz)
{
    EXPECT_NO_THROW(A.difz());
}



TEST_P(translate, can_insert_monome)
{
    polynome pol;
    EXPECT_NO_THROW(pol.insert(monome(GetParam(), 1, 1, 1)));
}

TEST_F(translate, can_solve)
{
    EXPECT_EQ(6, solve("A + B + C * A",a).get_size());
}



/*
TEST_F(translate, correct_add)
{
    auto tmp=solve("1 + 1",a);
    EXPECT_EQ(2, tmp.first);
}
TEST_F(translate, correct_sub)
{
    auto tmp=solve("- ( - 4 + 5 )",a);
    EXPECT_EQ(-1, tmp.first);
}
TEST_F(translate, cant_solve_with_incorrect_symbol)
{
    auto tmp=solve("- ( - 4aaaaa + 5 )",a);
    EXPECT_EQ(1, tmp.second);
}
TEST_F(translate, can_mult)
{
    auto tmp=solve("1 * 4.5",a);
    EXPECT_EQ(4.5, tmp.first);
}
TEST_F(translate, can_div)
{
    auto tmp=solve("1 / 5",a);
    EXPECT_EQ(0.2, tmp.first);
}

TEST_F(translate, cant_solve_with_incorrecr_brackets)
{
    auto tmp=solve("( 1 + 1 ) )",a);
    std::cout<<tmp.first;
    EXPECT_EQ(1, tmp.second);
}

TEST_F(translate, brackets_work)
{
    auto tmp=solve("1.5 * ( 10 + 4 ) / 7",a);
    EXPECT_EQ(3, tmp.first);
}
TEST_F(translate, cant_zero_div)
{
    auto tmp=solve("5 / 0",a);
    EXPECT_EQ(1, tmp.second);
}
TEST_F(translate, cant_calc_emty_brackets)
{
    auto tmp=solve("1 + ( )",a);
    EXPECT_EQ(1, tmp.second);
}

TEST_F(translate, can_neg_nmber)
{
    auto tmp=solve(" - 1 + 1",a);
    EXPECT_EQ(0, tmp.first);
}
TEST_F(translate, cant_solve_invalid)
{
    auto tmp=solve("* 1",a);
    EXPECT_EQ(0, tmp.first);
}
TEST_F(translate, can_solve_variable)
{
    a.push_back(1);a.push_back(2);
    auto tmp=solve("- a + b",a);
    EXPECT_EQ(1, tmp.first);
}
TEST_F(translate, cant_solve_invalid_variable_1)
{
    a.push_back(1);a.push_back(2);
    auto tmp=solve("- 1a + b",a);
    EXPECT_EQ(1, tmp.second);
}
TEST_F(translate, cant_solve_invalid_variable_2)
{
    a.push_back(1);a.push_back(2);
    auto tmp=solve("- (a + b",a);
    EXPECT_EQ(1, tmp.second);
}(*/
