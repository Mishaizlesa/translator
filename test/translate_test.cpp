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

TEST_P(translate, can_insert_monome)
{
    polynome pol;
    EXPECT_NO_THROW(pol.insert(monome(GetParam(), 1, 1, 1)));
}

TEST_F(translate, can_solve)
{
    EXPECT_EQ(6, solve("A + B + C * A",a).get_size());
}

TEST(translate_test, correct_add_with_similar_terms)
{
    polynome a, b, res, sum;
    a.insert(monome(1, 1, 1, 1));
    a.insert(monome(2, 2, 1, 1));

    b.insert(monome(3, 1, 1, 1));
    b.insert(monome(4, 2, 1, 1));

    res.insert(monome(4, 1, 1, 1));
    res.insert(monome(6, 2, 1, 1));

    bool eq = res == a + b;
    EXPECT_EQ(eq, true);
}

TEST(translate_test, correct_add)
{
    polynome a, b, res, sum;
    a.insert(monome(1, 1, 1, 1));
    a.insert(monome(2, 2, 1, 1));

    b.insert(monome(3, 1, 2, 1));
    b.insert(monome(4, 2, 2, 1));

    res.insert(monome(1, 1, 1, 1));
    res.insert(monome(2, 2, 1, 1));
    res.insert(monome(3, 1, 2, 1));
    res.insert(monome(4, 2, 2, 1));

    bool eq = res == a + b;
    EXPECT_EQ(eq, true);
}


TEST_F(translate, correct_add)
{
    auto res = solve("A + B", a);
    EXPECT_EQ(res.get_size(), 6);
    for (int i = 0; i < 6; i++)
    {
        bool eq = res[0].first == A + B;
        EXPECT_EQ(eq, true);
    }
}


TEST(translate_test, correct_sub)
{
    polynome a, b, res, sum;
    a.insert(monome(1, 1, 1, 1));
    a.insert(monome(2, 2, 1, 1));

    b.insert(monome(3, 1, 2, 1));
    b.insert(monome(4, 2, 2, 1));

    res.insert(monome(1, 1, 1, 1));
    res.insert(monome(2, 2, 1, 1));
    res.insert(monome(-3, 1, 2, 1));
    res.insert(monome(-4, 2, 2, 1));

    bool eq = res == a - b;
    EXPECT_EQ(eq, true);
}

TEST(translate_test, correct_sub_with_similar_terms)
{
    polynome a, b, res, sum;
    a.insert(monome(1, 1, 1, 1));
    a.insert(monome(2, 2, 1, 1));

    b.insert(monome(3, 1, 1, 1));
    b.insert(monome(4, 2, 1, 1));

    res.insert(monome(-2, 1, 1, 1));
    res.insert(monome(-2, 2, 1, 1));

    bool eq = res == a - b;
    EXPECT_EQ(eq, true);
}

TEST_F(translate, correct_sub)
{
    auto res = solve("A - B", a);
    EXPECT_EQ(res.get_size(), 6);
    auto sub = A - B;
    for (int i = 0; i < 6; i++)
    {
        bool eq = res[0].first == sub;
        EXPECT_EQ(eq, true);
    }
}

TEST(translate_test, correct_mul)
{
    polynome a, b, res, sum;
    a.insert(monome(1, 1, 1, 1));
    a.insert(monome(2, 2, 1, 1));

    b.insert(monome(3, 1, 1, 2));
    b.insert(monome(4, 2, 1, 2));

    res.insert(monome(3, 2, 2, 3));
    res.insert(monome(4, 3, 2, 3));

    res.insert(monome(6, 3, 2, 3));
    res.insert(monome(8, 4, 2, 3));

    bool eq = res == a * b;
    EXPECT_EQ(eq, true);
}

TEST_F(translate, correct_mul)
{
    auto res = solve("A * B", a);
    EXPECT_EQ(res.get_size(), 6);
    auto mul = A * B;
    for (int i = 0; i < 6; i++)
    {
        bool eq = res[0].first == mul;
        EXPECT_EQ(eq, true);
    }
}






TEST_F(translate, can_difx)
{
    EXPECT_NO_THROW(A.difx());
}

TEST(polynome_test, correct_difx)
{
    polynome A, res;
    A.insert(monome(5, 2, 2, 2));
    res.insert(monome(10, 1, 2, 2));
    bool eq = A.difx() == res;
    EXPECT_EQ(eq, true);
}
TEST_F(translate, can_dify)
{
    EXPECT_NO_THROW(A.dify());
}
TEST(polynome_test, correct_dify)
{
    polynome A, res;
    A.insert(monome(5, 2, 2, 2));
    res.insert(monome(10, 2, 1, 2));
    bool eq = A.dify() == res;
    EXPECT_EQ(eq, true);
}

TEST_F(translate, can_difz)
{
    EXPECT_NO_THROW(A.difz());
}
TEST(polynome_test, correct_difz)
{
    polynome A, res;
    A.insert(monome(5, 2, 2, 2));
    res.insert(monome(10, 2, 2, 1));
    bool eq = A.difz() == res;
    EXPECT_EQ(eq, true);
}
