#include "gtest/gtest.h"
#include <list>
#include "table.h"
#include "TableT.h"
#include "tree.h"
#include "TreeT.h"
#include "HashTable.h"
#include "hash_table.h"
template <typename T>
class FooTest : public testing::Test {
public:
    using MyTable = T;
};

using MyTypes = ::testing::Types<
    TableT<std::string, int>
    , Table<std::string, int>
    , TreeT<std::string, int>
    , Tree<std::string, int>
    , HashTable<int, std::string>
    , my_unordered_map<int, std::string>

>;
TYPED_TEST_SUITE(FooTest, MyTypes);

TYPED_TEST(FooTest, can_insert)
{
    typename TestFixture::MyTable values;
    EXPECT_NO_THROW(values.insert(std::make_pair("str", 5551)));
}

TYPED_TEST(FooTest, correct_value_after_insert)
{
    typename TestFixture::MyTable values;
    values.insert(std::make_pair("str", 5551));
    EXPECT_EQ(values["str"], 5551);
}

TYPED_TEST(FooTest, can_used_square_brackets)
{
    typename TestFixture::MyTable values;
    EXPECT_NO_THROW(values["de"] = 58);
}

TYPED_TEST(FooTest, square_brackets_from_a_non_existent_key_returns_the_default_value)
{
    typename TestFixture::MyTable values;
    EXPECT_EQ(values["de"], 0);
}

TYPED_TEST(FooTest, can_return_iterator_to_begining)
{
    typename TestFixture::MyTable values;
    EXPECT_NO_THROW(values.begin());
}

TYPED_TEST(FooTest, can_return_iterator_to_ending)
{
    typename TestFixture::MyTable values;
    EXPECT_NO_THROW(values.end());
}

TYPED_TEST(FooTest, can_erase)
{
    typename TestFixture::MyTable values;
    values["str"] = 5;
    EXPECT_NO_THROW(values.erase("str"));
}



TYPED_TEST(FooTest, after_erase_correct_value)
{
    typename TestFixture::MyTable values;
    values["str"] = 5;
    values.erase("str");
    EXPECT_EQ(values["str"], 0);
}






