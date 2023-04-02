
/*class translate : public ::testing::Test {
protected:
    std::vector<polynome>a;
};
TEST_F(translate, can_create_expr)
{
    EXPECT_EQ(12, solve("12",a).first + solve("12",a).second);
}
TEST_F(translate, cant_solve_empty)
{
    EXPECT_EQ(1, solve("",a).second);
}
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
/*
TEST_F(translate, can_solve_variable)
{
    a.push_back();a.push_back(2);
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
}
*/