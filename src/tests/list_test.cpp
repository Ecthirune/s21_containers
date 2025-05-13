#include <gtest/gtest.h>

#include <list>

#include "../s21_list/s21_list.h"

class ComplicatedClass {
 public:
  int* test;
  ComplicatedClass() {
    test = new int[2];
    test[0] = 5;
    // std::cout << "ComplicatedClass built" << std::endl;
  }
  ComplicatedClass(const ComplicatedClass& other) {
    test = new int[2];
    test[0] = other.test[0];
    // std::cout << "ComplicatedClass copied" << std::endl;
  }
  ~ComplicatedClass() {
    delete[] test;
    // std::cout << "ComplicatedClass deleted" << std::endl;
  }
};

TEST(ListTest, Default_Constructor) {
  s21::list<int> my_list;
  ASSERT_EQ(my_list.size(), 0);
}

TEST(ListTest, Initializer_List_Constructor) {
  s21::list my_list = {1, 2, 3, 4, 5};
  std::list compare_list = {1, 2, 3, 4, 5};
  ASSERT_EQ(my_list.size(), 5);
  ASSERT_EQ(my_list.front(), compare_list.front());
  ASSERT_EQ(my_list.back(), compare_list.back());
}

TEST(ListTest, Copy_list_constuctor) {
  s21::list list1 = {1, 2, 3, 4, 5};
  s21::list list2(list1);
  ASSERT_EQ(list2.size(), 5);
}

TEST(ListTest, assign_constructor) {
  s21::list list1 = {1, 2, 3, 4, 5};
  s21::list list2 = list1;
  ASSERT_EQ(list2.size(), 5);
}

TEST(ListTest, Complex_constructor) {
  s21::list<ComplicatedClass> my_list(2);
  ASSERT_EQ(my_list.size(), 2);
  ASSERT_EQ(my_list.begin()->value.test[0], 5);
}

TEST(ListTest, Insert_Into_Empty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  const int some_value = 42;

  auto it = my_list.insert(my_list.begin(), some_value);
  std_list.insert(std_list.begin(), 42);

  ASSERT_EQ(my_list.size(), 1);
  ASSERT_EQ(it->value, 42);
  ASSERT_EQ(*std_list.begin(), 42);
}

TEST(ListTest, Insert_At_End_Non_Empty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.insert(my_list.begin(), 1);
  std_list.push_back(1);

  auto it = my_list.insert(my_list.end(), 42);
  std_list.insert(std_list.end(), 42);

  ASSERT_EQ(my_list.size(), 2);
  ASSERT_EQ(my_list.back(), 42);
  ASSERT_EQ(std_list.back(), 42);
}

TEST(ListTest, Insert_At_Beginning_Non_Empty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.insert(my_list.begin(), 1);
  std_list.push_back(1);

  auto it = my_list.insert(my_list.begin(), 42);
  std_list.insert(std_list.begin(), 42);

  ASSERT_EQ(my_list.size(), 2);
  ASSERT_EQ(my_list.front(), 42);
  ASSERT_EQ(std_list.front(), 42);
}

TEST(ListTest, Insert_In_Middle) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.insert(my_list.begin(), 1);
  auto second_it = my_list.insert(my_list.end(), 3);
  std_list.push_back(1);
  std_list.push_back(3);

  auto it = my_list.insert(second_it, 42);
  auto std_it = std_list.insert(++std_list.begin(), 42);

  ASSERT_EQ(my_list.size(), 3);
  ASSERT_EQ(it->value, 42);
  ASSERT_EQ(*std_it, 42);
}

TEST(ListTest, Insert_Invalid_Iterator) {
  s21::list<int> my_list;
  my_list.insert(my_list.begin(), 1);
  s21::list<int> my_list2(5);
  s21::list<int>::iterator invalid_it = my_list2.begin();
  ASSERT_THROW(my_list.insert(invalid_it, 42), std::out_of_range);
}

TEST(ListTest, Clear) {
  s21::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);
  ASSERT_EQ(my_list.size(), 3);
  my_list.clear();
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_EQ(my_list.empty(), true);
}

TEST(ListTest, Erase_Head) {
  s21::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.erase(my_list.begin());
  ASSERT_EQ(my_list.size(), 1);
  ASSERT_EQ(my_list.begin()->value, 2);
  ASSERT_EQ(my_list.begin()->prev, nullptr);
}

TEST(ListTest, Erase_Head2) {
  s21::list<int> my_list;
  my_list.push_back(1);
  my_list.erase(my_list.begin());
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_EQ(my_list.begin(), nullptr);
  ASSERT_EQ(my_list.end(), nullptr);
}

TEST(ListTest, Erase_Tail) {
  s21::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  auto it = my_list.begin()->next;
  if (it) {
    my_list.erase(it);
  }
  ASSERT_EQ(my_list.size(), 1);
  ASSERT_EQ(my_list.back(), 1);
  ASSERT_EQ(my_list.begin()->next, nullptr);
}

TEST(ListTest, Erase_throw) {
  s21::list<int> my_list;
  ASSERT_THROW(my_list.erase(my_list.end()), std::out_of_range);
}

TEST(ListTest, pop_back_default) {
  s21::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);
  ASSERT_EQ(my_list.size(), 3);
  my_list.pop_back();
  ASSERT_EQ(my_list.size(), 2);
  ASSERT_EQ(my_list.back(), 2);
}

TEST(ListTest, pop_back_add_remove_single_entry) {
  s21::list<int> my_list;
  my_list.push_back(1);
  my_list.pop_back();
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_EQ(my_list.empty(), true);
}

TEST(ListTest, pop_back_throw) {
  s21::list<int> my_list;
  ASSERT_THROW(my_list.pop_back(), std::out_of_range);
}

TEST(ListTest, pish_front_default) {
  s21::list<int> my_list;
  my_list.push_front(1);
  my_list.push_front(2);
  ASSERT_EQ(my_list.size(), 2);
  ASSERT_EQ(my_list.front(), 2);
}

TEST(ListTest, push_front_add_remove_single_entry) {
  s21::list<int> my_list = {1, 2, 3, 4};
  my_list.push_front(10);
  ASSERT_EQ(my_list.size(), 5);
  ASSERT_EQ(my_list.front(), 10);
}


TEST(ListTest, Sort) {

  s21::list<int> my_list = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
  my_list.sort();

  ASSERT_EQ(my_list.size(), 11);
  ASSERT_EQ(my_list.front(), 1);
  ASSERT_EQ(my_list.back(), 9);
}

TEST(ListTest, Sort_Empty_List) {
  s21::list<int> my_list;
  my_list.sort();
  ASSERT_TRUE(my_list.empty());
}

TEST(ListTest, Move_Constructor) {
  s21::list<int> my_list = {1, 2, 3};
  s21::list<int> moved_list(std::move(my_list));
  ASSERT_TRUE(my_list.empty());
  ASSERT_EQ(moved_list.size(), 3);
  ASSERT_EQ(moved_list.front(), 1);
  ASSERT_EQ(moved_list.back(), 3);

}

TEST(ListTest, Assignment_Operator) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2;
  list2 = std::move(list1);
  ASSERT_TRUE(list1.empty());
  ASSERT_EQ(list2.size(), 3);
  ASSERT_EQ(list2.front(), 1);
}

TEST(ListTest, pop_front_default) {
  s21::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);
  ASSERT_EQ(my_list.size(), 3);
  my_list.pop_front();
  ASSERT_EQ(my_list.size(), 2);
  ASSERT_EQ(my_list.front(), 2);
  ASSERT_EQ(my_list.begin()->prev, nullptr);
  ASSERT_EQ(my_list.begin()->value, 2);
}

TEST(ListTest, pop_front_single)
{
  s21::list<int> my_list = {1};
  my_list.pop_front();
  ASSERT_TRUE(my_list.empty());
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_EQ(my_list.begin(), nullptr);
  ASSERT_EQ(my_list.end(), nullptr);
  ASSERT_THROW(my_list.pop_front(), std::out_of_range);
}

TEST(ListTest, swap)
{
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6};
  list1.swap(list2);
  ASSERT_EQ(list1.size(), 3);
  ASSERT_EQ(list2.size(), 3);
  ASSERT_EQ(list1.front(), 4);
  ASSERT_EQ(list1.back(), 6);
  ASSERT_EQ(list2.front(), 1);
  ASSERT_EQ(list2.back(), 3);
}

TEST(ListTest, merge)
{
  s21::list<int> list1 = {1, 3, 5};
  s21::list<int> list2 = {2, 4, 6};
  list1.merge(list2);
  ASSERT_EQ(list1.size(), 6);
  ASSERT_EQ(list1.front(), 1);
  ASSERT_EQ(list1.back(), 6);

}

TEST(ListTest, merge_empty_with_filled)
{
  s21::list<int> list1;
  s21::list<int> list2 = {1, 3, 5};
  list1.merge(list2);
  ASSERT_EQ(list1.size(), 3);
  ASSERT_EQ(list1.front(), 1);
  ASSERT_EQ(list1.back(), 5);
}

