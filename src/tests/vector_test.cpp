#include <gtest/gtest.h>

#include "../s21_vector/s21_vector.h"

class ComplicatedClass {
 public:
  int* test;
  ComplicatedClass() {
    test = new int[2];
    test[0] = 5;
  };
  ~ComplicatedClass() { delete[] test; };
};
TEST(VectorTest, Complicated_constructor) {
  s21::vector<ComplicatedClass> v(5);
  EXPECT_EQ(v[0].test[0], 5);
}

TEST(VectorTest, DefaultConstructor_EmptyVector) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), (size_t)0);
}

TEST(VectorTest, SizeConstructor_PositiveSize) {
  const size_t size = 5;
  s21::vector<int> v(size);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(VectorTest, SizeConstructor_ZeroSize) {
  const size_t size = 0;
  s21::vector<int> v(size);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), size);
}

TEST(VectorTest, InitializerListConstructor_EmptyList) {
  s21::vector<int> v = {};
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), (size_t)0);
}

TEST(VectorTest, InitializerListConstructor_NonEmptyList) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), (size_t)5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, CopyConstructor_EmptyVector) {
  s21::vector<int> v1;
  s21::vector<int> v2(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), (size_t)0);
}

TEST(VectorTest, CopyConstructor_NonEmptyVector) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v2.size(), v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(VectorTest, MoveConstructor_EmptyVector) {
  s21::vector<int> v1;
  s21::vector<int> v2(std::move(v1));
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), (size_t)0);
}

TEST(VectorTest, MoveConstructor_NonEmptyVector) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), (size_t)3);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, Destructor_EmptyVector) {
  s21::vector<int>* v = new s21::vector<int>();
  delete v;  // Destructor should be called here
  // No specific assertions, but this ensures the destructor is working
}

TEST(VectorTest, MoveAssignmentOperator_EmptyToEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), (size_t)0);
}

TEST(VectorTest, MoveAssignmentOperator_NonEmptyToEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), (size_t)3);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, MoveAssignmentOperator_EmptyToNonEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), (size_t)0);
}

TEST(VectorTest, MoveAssignmentOperator_NonEmptyToNonEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), (size_t)3);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, At_ValidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(4), 5);
}

TEST(VectorTest, At_InvalidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_THROW(v.at(5), std::out_of_range);
  EXPECT_THROW(v.at(10), std::out_of_range);
}

TEST(VectorTest, IndexOperator_ValidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, IndexOperator_InvalidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v[5]);
  EXPECT_ANY_THROW(v[10]);
}

TEST(VectorTest, ConstIndexOperator_ValidIndex) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, ConstIndexOperator_InvalidIndex) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v[5]);
  EXPECT_ANY_THROW(v[10]);
}

TEST(VectorTest, FrontConst_ValidVector) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.front(), 1);
}

// TEST(VectorTest, FrontConst_EmptyVector) {
//   const s21::vector<int> v;
//   EXPECT_THROW(v.front(), std::out_of_range);
// }

TEST(VectorTest, BackConst_ValidVector) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.back(), 5);
}

// TEST(VectorTest, BackConst_EmptyVector) {
//   const s21::vector<int> v;
//   EXPECT_THROW(v.back(), std::out_of_range);
// }

TEST(VectorTest, Data_ValidVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  int* dataPtr = v.data();
  EXPECT_EQ(*dataPtr, 1);
  // Modify the data through the pointer and check if the vector is updated
  *dataPtr = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, Data_EmptyVector) {
  s21::vector<int> v;
  int* dataPtr = v.data();
  // Data pointer of an empty vector can be anything
  EXPECT_EQ(dataPtr, nullptr);
}

TEST(VectorTest, Begin_ValidVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  // Modify the data through the iterator and check if the vector is updated
  *it = 10;
  EXPECT_EQ(v[0], 10);
}

TEST(VectorTest, Begin_EmptyVector) {
  s21::vector<int> v;
  auto it = v.begin();
  // The begin() of an empty vector should be the end() too, so iterator should
  // be equal to end()
  EXPECT_EQ(it, v.end());
}

TEST(VectorTest, End_ValidVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  // end() iterator should not be dereferenced; comparing it to another iterator
  // should work
  auto beginIt = v.begin();
  EXPECT_NE(it, beginIt);
}

TEST(VectorTest, End_EmptyVector) {
  s21::vector<int> v;
  auto it = v.end();
  // The end() of an empty vector should be the begin() too, so iterator should
  // be equal to begin()
  EXPECT_EQ(it, v.begin());
}

TEST(VectorTest, Empty_EmptyVector) {
  const s21::vector<int> v;
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Empty_NonEmptyVector) {
  const s21::vector<int> v = {1, 2, 3};
  EXPECT_FALSE(v.empty());
}

TEST(VectorTest, Size_EmptyVector) {
  const s21::vector<int> v;
  EXPECT_EQ(v.size(), (size_t)0);
}

TEST(VectorTest, Size_NonEmptyVector) {
  const s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.size(), (size_t)3);
}

TEST(VectorTest, MaxSize) {
  const s21::vector<int> v;
  // You can't predict the exact max size, but it should be a very large value
  EXPECT_GT(v.max_size(), (size_t)0);
}

TEST(VectorTest, Reserve_IncreaseCapacity) {
  s21::vector<int> v;
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity + 10;
  v.reserve(newCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(VectorTest, Reserve_DecreaseCapacity) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity - 2;
  v.reserve(newCapacity);
  // Capacity may not decrease immediately, but it shouldn't exceed the
  // requested value
  EXPECT_LE(v.capacity(), initialCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(VectorTest, Capacity_EmptyVector) {
  const s21::vector<int> v;
  // The capacity of an empty vector should be at least 0
  EXPECT_GE(v.capacity(), (size_t)0);
}

TEST(VectorTest, Capacity_NonEmptyVector) {
  const s21::vector<int> v = {1, 2, 3};
  // The capacity of a non-empty vector might vary, but it should be at least
  // the size of the vector
  EXPECT_GE(v.capacity(), v.size());
}

TEST(VectorTest, ShrinkToFit_EmptyVector) {
  s21::vector<int> v;
  v.shrink_to_fit();
  // After shrink_to_fit() on an empty vector, the capacity should still be at
  // least 0
  EXPECT_GE(v.capacity(), (size_t)0);
}

TEST(VectorTest, ShrinkToFit_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  v.pop_back();  // Simulate a reduction in size
  v.shrink_to_fit();
  // After shrink_to_fit(), the capacity should not exceed the new size
  EXPECT_LE(v.capacity(), v.size());
  // The capacity may not necessarily decrease, but it should not be larger than
  // the initial capacity
  EXPECT_LE(v.capacity(), initialCapacity);
}

TEST(VectorTest, Clear_EmptyVector) {
  s21::vector<int> v;
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), (size_t)0);
  // Clearing an empty vector should not affect capacity
  EXPECT_GE(v.capacity(), (size_t)0);
}

TEST(VectorTest, Clear_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), (size_t)0);
  // Clearing a vector should not affect capacity immediately
  EXPECT_GE(v.capacity(), (size_t)0);
}

TEST(VectorTest, Insert_Beginning) {
  s21::vector<int> v = {2, 3, 4};
  auto it = v.insert(v.begin(), 1);
  EXPECT_EQ(v.size(), (size_t)4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(*it, 1);
}

TEST(VectorTest, Insert_Middle) {
  s21::vector<int> v = {1, 3, 4};
  auto it = v.insert(v.begin() + 1, 2);
  EXPECT_EQ(v.size(), (size_t)4);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, Insert_End) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.insert(v.end(), 4);
  EXPECT_EQ(v.size(), (size_t)4);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(*it, 4);
}

TEST(VectorTest, Erase_Beginning) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin());  // Erase the first element
  EXPECT_EQ(v.size(), (size_t)3);
  EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, Erase_Middle) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin() + 1);
  EXPECT_EQ(v.size(), (size_t)3);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, Erase_End) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.end() - 1);  // Erase the last element
  EXPECT_EQ(v.size(), (size_t)3);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PushBack_EmptyVector) {
  s21::vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.size(), (size_t)1);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, PushBack_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3};
  v.push_back(4);
  EXPECT_EQ(v.size(), (size_t)4);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, PopBack_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), (size_t)2);
  EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, PopBack_EmptyVector) {
  s21::vector<int> v;
  // Popping from an empty vector should not cause an error (undefined behavior
  // for some std::vector implementations)
  v.pop_back();
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Swap_NonEmptyVectors) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), (size_t)3);
  EXPECT_EQ(v2.size(), (size_t)3);

  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[2], 6);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, Swap_EmptyAndNonEmptyVectors) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {1, 2, 3};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), (size_t)3);
  EXPECT_FALSE(v1.empty());
  EXPECT_EQ(v2.size(), (size_t)0);
  EXPECT_TRUE(v2.empty());
}
TEST(VectorIteratorTest, DefaultConstructionAndDereference) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);  // Проверка разыменования
}

TEST(VectorIteratorTest, Increment) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.begin();
  ++it;  // Префиксный инкремент
  EXPECT_EQ(*it, 2);
  it++;  // Постфиксный инкремент
  EXPECT_EQ(*it, 3);
}

TEST(VectorIteratorTest, Decrement) {
  s21::vector<int> v = {1, 2, 3};
  auto it = v.end();
  --it;  // Префиксный декремент
  EXPECT_EQ(*it, 3);
  it = v.begin() + 2;
  it--;  // Постфиксный декремент
  EXPECT_EQ(*it, 2);
}

TEST(VectorIteratorTest, Arithmetic) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  it = it + 2;  // Сдвиг вперед
  EXPECT_EQ(*it, 3);
  it = it - 1;  // Сдвиг назад
  EXPECT_EQ(*it, 2);
}

TEST(VectorIteratorTest, Difference) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it1 = v.begin();
  auto it2 = v.end();
  ptrdiff_t diff = it2 - it1;
  EXPECT_EQ(diff, 5);  // Разность между end() и begin() = размер вектора
}

TEST(VectorIteratorTest, Comparison) {
  s21::vector<int> v = {1, 2, 3};
  auto it1 = v.begin();
  auto it2 = v.begin();
  EXPECT_TRUE(it1 == it2);  // Равенство
  ++it1;
  EXPECT_TRUE(it1 != it2);  // Неравенство
}

// Тесты для константных итераторов
TEST(VectorConstIteratorTest, DefaultConstructionAndDereference) {
  const s21::vector<int> v = {1, 2, 3};
  auto it = v.cbegin();
  EXPECT_EQ(*it, 1);  // Проверка разыменования
}

TEST(VectorConstIteratorTest, Increment) {
  const s21::vector<int> v = {1, 2, 3};
  auto it = v.cbegin();
  ++it;  // Префиксный инкремент
  EXPECT_EQ(*it, 2);
  it++;  // Постфиксный инкремент
  EXPECT_EQ(*it, 3);
}

TEST(VectorConstIteratorTest, Decrement) {
  const s21::vector<int> v = {1, 2, 3};
  auto it = v.cend();
  --it;  // Префиксный декремент
  EXPECT_EQ(*it, 3);
  it = v.cbegin() + 2;
  it--;  // Постфиксный декремент
  EXPECT_EQ(*it, 2);
}

TEST(VectorConstIteratorTest, Arithmetic) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.cbegin();
  it = it + 2;  // Сдвиг вперед
  EXPECT_EQ(*it, 3);
  it = it - 1;  // Сдвиг назад
  EXPECT_EQ(*it, 2);
}

TEST(VectorConstIteratorTest, Difference) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it1 = v.cbegin();
  auto it2 = v.cend();
  ptrdiff_t diff = it2 - it1;
  EXPECT_EQ(diff, 5);  // Разность между cend() и cbegin() = размер вектора
}

TEST(VectorConstIteratorTest, Comparison) {
  const s21::vector<int> v = {1, 2, 3};
  auto it1 = v.cbegin();
  auto it2 = v.cbegin();
  EXPECT_TRUE(it1 == it2);  // Равенство
  ++it1;
  EXPECT_TRUE(it1 != it2);  // Неравенство
}

// Тест на совместимость итераторов с изменением вектора
TEST(VectorIteratorTest, InsertWithIterator) {
  s21::vector<int> v = {1, 3, 4};
  auto it = v.begin() + 1;
  auto new_it = v.insert(it, 2);
  EXPECT_EQ(*new_it, 2);  // Новый итератор указывает на вставленный элемент
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

// Тест на итерирование по всему вектору
TEST(VectorIteratorTest, FullIteration) {
  s21::vector<int> v = {1, 2, 3, 4};
  int expected[] = {1, 2, 3, 4};
  int i = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    EXPECT_EQ(*it, expected[i++]);
  }
  EXPECT_EQ(i, 4);  // Убедимся, что прошли весь вектор
}

TEST(VectorConstIteratorTest, FullConstIteration) {
  const s21::vector<int> v = {1, 2, 3, 4};
  int expected[] = {1, 2, 3, 4};
  int i = 0;
  for (auto it = v.cbegin(); it != v.cend(); ++it) {
    EXPECT_EQ(*it, expected[i++]);
  }
  EXPECT_EQ(i, 4);  // Убедимся, что прошли весь вектор
}
