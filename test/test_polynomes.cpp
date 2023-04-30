#include "stack.h"
#include <gtest/gtest.h>
#include "polynome.h"
class polunome_f :
    public ::testing::TestWithParam<int> {

protected:
    //
    polynome A, B, C, D;

    polunome_f()
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

    }

};

INSTANTIATE_TEST_SUITE_P(translate_test, polunome_f, ::testing::Values(-1, 0, 1));


TEST_P(polunome_f, can_create_monome)
{
    EXPECT_NO_THROW(monome(GetParam(), 1, 1, 1));
}
TEST(test, can_create_polynome)
{
    EXPECT_NO_THROW(polynome());
}

TEST_P(polunome_f, can_insert_monome)
{
    polynome pol;
    EXPECT_NO_THROW(pol.insert(monome(GetParam(), 1, 1, 1)));
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


TEST(polynome_test, empty_pol_equal_zero_pol)
{
    polynome empty, zero;
    zero.insert(monome(0, 0, 0, 0));
    bool eq = empty == zero;
    EXPECT_EQ(eq, true);
}
TEST_F(polunome_f, correct_mul_by_zero)
{
    polynome zero;
    polynome mul;
    mul.insert(monome(0, 0, 0, 0));

    bool eq = A * zero == mul;
    EXPECT_EQ(eq, true);

}

TEST(translate_test, correct_div)
{
    polynome a, b, res, sum;
    a.insert(monome(1, 1, 1, 3));
    a.insert(monome(2, 2, 1, 1));

    b.insert(monome(3, 1, 1, 2));

    res.insert(monome(1.0/3, 0, 0, 1));


    bool eq = res == a / b;
    EXPECT_EQ(eq, true);
}



TEST_F(polunome_f, can_difx)
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
TEST_F(polunome_f, can_dify)
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

TEST_F(polunome_f, can_difz)
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
