#include "stack.h"
#include <gtest.h>

TEST(stack, can_create_stack)
{
    EXPECT_NO_THROW(stack<int>());
}

TEST(stack, cant_create_negative_size)
{
    EXPECT_ANY_THROW(stack<int>(-1));
}
TEST(stack, size_work)
{
    stack<int>a;
    a.push(4);
    EXPECT_EQ(a.get_size(), 1);
}
TEST(stack, cant_front_empty_stack)
{
    stack<int>a;
    EXPECT_ANY_THROW(a.top());
}

TEST(stack, correct_push_stack)
{
    stack<int>a;
    a.push(4);
    a.push(10);
    EXPECT_EQ(10, a.top());
}

TEST(stack, cant_push_too_much)
{
    stack<int>a(0);
    EXPECT_ANY_THROW(a.push(1));
}

TEST(stack, cant_pop_empty)
{
    stack<int>q;
    EXPECT_ANY_THROW(q.pop());
}
TEST(stack, correct_pop)
{
    stack<int>q;
    q.push(3);
    q.push(4);
    q.pop();
    EXPECT_EQ(q.top(), 3);
}

