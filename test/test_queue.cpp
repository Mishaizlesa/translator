#include "queue.h"
#include <gtest.h>

TEST(queue, can_create_q)
{
    EXPECT_NO_THROW(queue<int>());
}

TEST(queue, cant_create_negative_size)
{
    EXPECT_ANY_THROW(queue<int>(-1));
}
TEST(queue, size_work)
{
    queue<int>a;
    a.push(4);
    EXPECT_EQ(a.get_size(), 1);
}
TEST(queue, cant_front_empty_q)
{
    queue<int>a;
    EXPECT_ANY_THROW(a.front());
}

TEST(queue, correct_push_q)
{
    queue<int>a;
    a.push(4);
    a.push(10);
    EXPECT_EQ(4, a.front());
}

TEST(queue, cant_push_too_much)
{
    queue<int>a(0);
    EXPECT_ANY_THROW(a.push(1));
}

TEST(queue, cant_pop_empty)
{
    queue<int>q;
    EXPECT_ANY_THROW(q.pop());
}
TEST(queue, correct_pop)
{
    queue<int>q;
    q.push(3);
    q.push(4);
    q.pop();
    EXPECT_EQ(q.front(), 4);
}

