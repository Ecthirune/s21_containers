#include "../s21_list/s21_list.h"

#include <gtest/gtest.h>
#include <list>

class ComplicatedClass {
 public:
  int* test;
  ComplicatedClass() {
    test = new int[2];
    test[0] = 5;
    std::cout << "ComplicatedClass built" << std::endl;
  }
  ComplicatedClass(const ComplicatedClass& other) {
    test = new int[2];
    test[0] = other.test[0];
    std::cout << "ComplicatedClass copied" << std::endl;
  }
  ~ComplicatedClass() {
    delete[] test;
    std::cout << "ComplicatedClass deleted" << std::endl;
  }
};


TEST(ListTest, Default_Constructor)
{
    S21::list<int> my_list;
    ASSERT_EQ(my_list.size(), 0);
}

TEST(ListTest, Initializer_List_Constructor)
{

	S21::list my_list = {1,2,3,4,5};
std::list compare_list = {1,2,3,4,5};
}

TEST(ListTest, Copy_list_constuctor)
{
	S21::list list1 = {1,2,3,4,5};
	S21::list list2 (list1);
}

TEST(ListTest, assign_constructor)
{
	S21::list list1 = {1,2,3,4,5};
	S21::list list2 = list1;
}

TEST(ListTest, Complex_constructor) {
  std::cout << "Creating list\n";
  S21::list<ComplicatedClass> list(2);
  std::cout << "Accessing front\n";
  std::cout << list.front().test[0] << std::endl;
  std::cout << "Test end\n";
}

TEST(ListTest, Insert_At_Beginning) {
    S21::list<int> my_list;
    std::list<int> std_list;
    const int  some_value = 42;

    my_list.insert(my_list.begin(), some_value);
    // std_list.insert(std_list.begin(), 42);
  
    // ASSERT_EQ(my_list.begin().value, 42);
    // ASSERT_EQ(*std_list.begin(), 42);
  }

/*
TEST(ListTest, Clear) {
  S21::list<int> lst;
  lst.push_back(1);  
  lst.push_back(2);
  lst.push_back(3);
  ASSERT_EQ(lst.size_, 3);  
  lst.clear();
  ASSERT_EQ(lst.size_, 0);
  ASSERT_EQ(lst.head_, nullptr);
  ASSERT_EQ(lst.tail_, nullptr);
}
*/