#include "solve_expr.h"
#include <gtest.h>
#include <iostream>
TEST(State, can_create_expr)
{
    EXPECT_EQ(12, solve("12").first + solve("12").second);
}
TEST(State, cant_solve_empty)
{
    EXPECT_EQ(1, solve("").second);
}
TEST(State, correct_add)
{
    auto tmp=solve("1 + 1");
    EXPECT_EQ(2, tmp.first);
}
TEST(State, correct_sub)
{
    auto tmp=solve("- ( - 4 + 5 )");
    EXPECT_EQ(-1, tmp.first);
}
TEST(State, cant_solve_with_incorrect_symbol)
{
    auto tmp=solve("- ( - 4aaaaa + 5 )");
    EXPECT_EQ(1, tmp.second);
}
TEST(State, can_mult)
{
    auto tmp=solve("1 * 4.5");
    EXPECT_EQ(4.5, tmp.first);
}
TEST(State, can_div)
{
    auto tmp=solve("1 / 5");
    EXPECT_EQ(0.2, tmp.first);
}

TEST(State, cant_solve_with_incorrecr_brackets)
{
    auto tmp=solve("( 1 + 1 ) )");
    std::cout<<tmp.first;
    EXPECT_EQ(1, tmp.second);
}

TEST(State, brackets_work)
{
    auto tmp=solve("1.5 * ( 10 + 4 ) / 7");
    EXPECT_EQ(3, tmp.first);
}
TEST(State, cant_zero_div)
{
    auto tmp=solve("5 / 0");
    EXPECT_EQ(1, tmp.second);
}
TEST(State, cant_calc_emty_brackets)
{
    auto tmp=solve("1 + ( )");
    EXPECT_EQ(1, tmp.second);
}

TEST(State, can_neg_nmber)
{
    auto tmp=solve(" - 1 + 1");
    EXPECT_EQ(0, tmp.first);
}
TEST(State, cant_solve_invalid)
{
    auto tmp=solve("* 1");
    EXPECT_EQ(0, tmp.first);
}

