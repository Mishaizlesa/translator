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

TEST_F(translate, can_solve)
{
    EXPECT_EQ(6, solve("A + B + C * A",a).get_size());
}

TEST_F(translate, correct_add)
{
    auto res = solve("A + B", a);
    EXPECT_EQ(res.get_size(), 6);
    for (int i = 0; i < res.get_size(); i++)
    {
        EXPECT_TRUE(res[0].first == A + B);
    }
}

TEST_F(translate, correct_sub)
{
    auto res = solve("A - B", a);
    EXPECT_EQ(res.get_size(), 6);
    auto sub = A - B;
    for (int i = 0; i < res.get_size(); i++)
    {
        EXPECT_TRUE(res[0].first == sub);
    }
}

TEST_F(translate, correct_mul)
{
    auto res = solve("A * B", a);
    EXPECT_EQ(res.get_size(), 6);
    auto mul = A * B;
    for (int i = 0; i < res.get_size(); i++)
    {
        EXPECT_TRUE(res[0].first == mul);
    }
}


TEST_F(translate, correct_div)
{
    auto res = solve("A / B", a);
    EXPECT_EQ(res.get_size(), 6);
    auto div = A / B;
    for (int i = 0; i < res.get_size(); i++)
    {
        EXPECT_TRUE(res[0].first == div);
    }
}


TEST_F(translate, correct_priority_of_oper1)
{
    auto res = solve("A + B * C", a);
    EXPECT_EQ(res.get_size(), 6);
    auto ans = B * C;
    ans = A + ans;
    for (int i = 0; i < 6; i++)
    {
        EXPECT_TRUE(res[0].first == ans);
    }
}

TEST_F(translate, correct_priority_of_oper2)
{
    auto res = solve("( A + B ) * C", a);
    EXPECT_EQ(res.get_size(), 6);
    auto ans = A + B;
    ans = ans * C;
    for (int i = 0; i < res.get_size(); i++)
    {
        EXPECT_TRUE(res[0].first == ans);
    }
}


TEST_F(translate, cant_solve_expr_with_invalid_lexems)
{
    auto res = solve("A < 3", a);
    EXPECT_EQ(res.get_size(), 0);
}