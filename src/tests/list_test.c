#include "../s21_list/s21_list.h"

#include <gtest/gtest.h>


TEST(ListTest, Default_Constructor)
{
    S21::list<int> my_list;
    ASSERT_EQ(my_list.size(), 0);
}

TEST(ListTest, Initializer_List_Constructor)
{
    std::initializer_list<int> init_list = {1, 2, 3, 4, 5};

}