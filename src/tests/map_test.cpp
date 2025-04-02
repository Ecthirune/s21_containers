#include <gtest/gtest.h>
#include "../s21_map/s21_map.h"
#include "../s21_vector/s21_vector.h"

TEST(MapTest, Default_constructor) {
    S21::map<int, std::string> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, Initializer_List_Constructor) {
    S21::map<int, std::string> m = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };
    EXPECT_EQ(m.size(), 3);
    EXPECT_EQ(m[1], "one");
    EXPECT_EQ(m[2], "two");
    EXPECT_EQ(m[3], "three");
}

TEST(MapTest, Copy_Constructor) {
    S21::map<int, std::string> m1 = {{1, "one"}, {2, "two"}};
    S21::map<int, std::string> m2(m1);
    EXPECT_EQ(m2.size(), 2);
    EXPECT_EQ(m2[1], "one");
    EXPECT_EQ(m2[2], "two");
}

TEST(MapTest, Move_Constructor) {
    S21::map<int, std::string> m1 = {{1, "one"}, {2, "two"}};
    S21::map<int, std::string> m2(std::move(m1));
    EXPECT_EQ(m2.size(), 2);
    EXPECT_EQ(m2[1], "one");
    EXPECT_EQ(m2[2], "two");
    EXPECT_TRUE(m1.empty());
}

TEST(MapTest, Insert) {
    S21::map<int, std::string> m;
    auto result = m.insert({1, "one"});
    EXPECT_TRUE(result.second);
    EXPECT_EQ(result.first->first, 1);
    EXPECT_EQ(result.first->second, "one");
    
    // Попытка вставить существующий ключ
    result = m.insert({1, "one_again"});
    EXPECT_FALSE(result.second);
}

TEST(MapTest, Insert_Or_Assign) {
    S21::map<int, std::string> m;
    auto result = m.insert_or_assign(1, "one");
    EXPECT_TRUE(result.second);
    EXPECT_EQ(m[1], "one");
    
    result = m.insert_or_assign(1, "one_updated");
    EXPECT_FALSE(result.second);
    EXPECT_EQ(m[1], "one_updated");
}

TEST(MapTest, Erase) {
    S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto it = m.find(2);
    m.erase(it);
    EXPECT_EQ(m.size(), 2);
    EXPECT_FALSE(m.contains(2));
}

TEST(MapTest, Clear) {
    S21::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    m.clear();
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, Swap) {
    S21::map<int, std::string> m1 = {{1, "one"}};
    S21::map<int, std::string> m2 = {{2, "two"}};
    m1.swap(m2);
    EXPECT_EQ(m1.size(), 1);
    EXPECT_EQ(m2.size(), 1);
    EXPECT_EQ(m1[2], "two");
    EXPECT_EQ(m2[1], "one");
}

TEST(MapTest, Merge) {
    S21::map<int, std::string> m1 = {{1, "one"}};
    S21::map<int, std::string> m2 = {{2, "two"}};
    m1.merge(m2);
    EXPECT_EQ(m1.size(), 2);
    EXPECT_EQ(m1[1], "one");
    EXPECT_EQ(m1[2], "two");
    EXPECT_TRUE(m2.empty());
}

TEST(MapTest, Contains) {
    S21::map<int, std::string> m = {{1, "one"}};
    EXPECT_TRUE(m.contains(1));
    EXPECT_FALSE(m.contains(2));
}

TEST(MapTest, At) {
    S21::map<int, std::string> m = {{1, "one"}};
    EXPECT_EQ(m.at(1), "one");
    EXPECT_THROW(m.at(2), std::out_of_range);
}

TEST(MapTest, Operator_Brackets) {
    S21::map<int, std::string> m;
    m[1] = "one";
    EXPECT_EQ(m[1], "one");
    EXPECT_EQ(m[2], ""); // Должен создать элемент с пустым значением
}

TEST(MapTest, Iterator) {
    S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    int count = 0;
    for (auto it = m.begin(); it != m.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

TEST(MapTest, Const_Iterator) {
    const S21::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    int count = 0;
    for (auto it = m.begin(); it != m.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST(MapTest, Max_Size) {
    S21::map<int, std::string> m;
    EXPECT_GT(m.max_size(), 0);
}

TEST(MapTest, Empty) {
    S21::map<int, std::string> m;
    EXPECT_TRUE(m.empty());
    m[1] = "one";
    EXPECT_FALSE(m.empty());
}

TEST(MapTest, Size) {
    S21::map<int, std::string> m;
    EXPECT_EQ(m.size(), 0);
    m[1] = "one";
    EXPECT_EQ(m.size(), 1);
    m[2] = "two";
    EXPECT_EQ(m.size(), 2);
}

TEST(MapTest, Find) {
    S21::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    auto it = m.find(1);
    EXPECT_NE(it, m.end());
    EXPECT_EQ(it->first, 1);
    EXPECT_EQ(it->second, "one");
    
    it = m.find(3);
    EXPECT_EQ(it, m.end());
}

TEST(MapTest, Const_Find) {
    const S21::map<int, std::string> m = {{1, "one"}};
    auto it = m.find(1);
    EXPECT_NE(it, m.end());
    EXPECT_EQ(it->first, 1);
    EXPECT_EQ(it->second, "one");
}

TEST(MapTest, Assignment_Operator) {
    S21::map<int, std::string> m1 = {{1, "one"}};
    S21::map<int, std::string> m2;
    m2 = m1;
    EXPECT_EQ(m2.size(), 1);
    EXPECT_EQ(m2[1], "one");
}

TEST(MapTest, Move_Assignment_Operator) {
    S21::map<int, std::string> m1 = {{1, "one"}};
    S21::map<int, std::string> m2;
    m2 = std::move(m1);
    EXPECT_EQ(m2.size(), 1);
    EXPECT_EQ(m2[1], "one");
    EXPECT_TRUE(m1.empty());
}

TEST(MapTest, Rotate_Right) {
    S21::map<int, std::string> m;
    
    // Создаем ситуацию для правостороннего вращения
    // Вставляем элементы в определенном порядке
    m.insert({3, "three"});
    m.insert({2, "two"});
    m.insert({1, "one"});
    
    // Проверяем, что элементы находятся в правильном порядке
    auto it = m.begin();
    EXPECT_EQ(it->first, 1);
    EXPECT_EQ(it->second, "one");
    ++it;
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, "two");
    ++it;
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, "three");
    
    // Проверяем размер
    EXPECT_EQ(m.size(), 3);
    
    // Проверяем, что все элементы доступны
    EXPECT_EQ(m[1], "one");
    EXPECT_EQ(m[2], "two");
    EXPECT_EQ(m[3], "three");
    
    // Проверяем, что дерево остается сбалансированным
    // (все операции должны работать корректно после вращения)
    m.erase(m.find(2));
    EXPECT_EQ(m.size(), 2);
    EXPECT_FALSE(m.contains(2));
    EXPECT_TRUE(m.contains(1));
    EXPECT_TRUE(m.contains(3));
}

TEST(MapTest, Assignment_Operator_With_Empty_Map) {
    S21::map<int, std::string> m1 = {{1, "one"}, {2, "two"}};
    S21::map<int, std::string> m2; // пустой map
    
    // Присваиваем пустой map
    m1 = m2;
    
    // Проверяем, что m1 стал пустым
    EXPECT_TRUE(m1.empty());
    EXPECT_EQ(m1.size(), 0);
    
    // Проверяем, что m2 остался пустым
    EXPECT_TRUE(m2.empty());
    EXPECT_EQ(m2.size(), 0);
    
    // Проверяем, что попытка доступа к элементам вызывает исключение
    EXPECT_THROW(m1.at(1), std::out_of_range);
    EXPECT_FALSE(m1.contains(1));
}

TEST(MapTest, Erase_Leaf_Node) {
    S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto it = m.find(3); // листовой узел
    m.erase(it);
    EXPECT_EQ(m.size(), 2);
    EXPECT_FALSE(m.contains(3));
    EXPECT_TRUE(m.contains(1));
    EXPECT_TRUE(m.contains(2));
}

TEST(MapTest, Erase_Node_With_Left_Child_Only) {
    S21::map<int, std::string> m;
    // Создаем ситуацию, когда узел имеет только левого потомка
    m.insert({3, "three"});
    m.insert({2, "two"});
    m.insert({1, "one"});
    auto it = m.find(2); // узел с левым потомком
    m.erase(it);
    EXPECT_EQ(m.size(), 2);
    EXPECT_FALSE(m.contains(2));
    EXPECT_TRUE(m.contains(1));
    EXPECT_TRUE(m.contains(3));
}

TEST(MapTest, Erase_Node_With_Right_Child_Only) {
    S21::map<int, std::string> m;
    // Создаем ситуацию, когда узел имеет только правого потомка
    m.insert({1, "one"});
    m.insert({2, "two"});
    m.insert({3, "three"});
    auto it = m.find(2); // узел с правым потомком
    m.erase(it);
    EXPECT_EQ(m.size(), 2);
    EXPECT_FALSE(m.contains(2));
    EXPECT_TRUE(m.contains(1));
    EXPECT_TRUE(m.contains(3));
}

TEST(MapTest, Erase_Node_With_Both_Children) {
    S21::map<int, std::string> m;
    // Создаем ситуацию, когда узел имеет обоих потомков
    m.insert({4, "four"});
    m.insert({2, "two"});
    m.insert({6, "six"});
    m.insert({1, "one"});
    m.insert({3, "three"});
    m.insert({5, "five"});
    m.insert({7, "seven"});
    
    auto it = m.find(4); // корневой узел с обоими потомками
    m.erase(it);
    
    EXPECT_EQ(m.size(), 6);
    EXPECT_FALSE(m.contains(4));
    EXPECT_TRUE(m.contains(1));
    EXPECT_TRUE(m.contains(2));
    EXPECT_TRUE(m.contains(3));
    EXPECT_TRUE(m.contains(5));
    EXPECT_TRUE(m.contains(6));
    EXPECT_TRUE(m.contains(7));
}

TEST(MapTest, Erase_Root_Node) {
    S21::map<int, std::string> m = {{1, "one"}};
    auto it = m.begin();
    m.erase(it);
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, Erase_All_Elements) {
    S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    while (!m.empty()) {
        auto it = m.begin();
        m.erase(it);
    }
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, Erase_Node_With_Left_Child_Only_Complex) {
    S21::map<int, std::string> m;
    // Создаем более сложную структуру с узлом, имеющим только левого потомка
    m.insert({5, "five"});
    m.insert({3, "three"});
    m.insert({7, "seven"});
    m.insert({2, "two"});
    m.insert({4, "four"});
    m.insert({6, "six"});
    m.insert({1, "one"}); // Добавляем левого потомка для узла 2
    
    auto it = m.find(2); // узел с левым потомком
    m.erase(it);
    
    EXPECT_EQ(m.size(), 6);
    EXPECT_FALSE(m.contains(2));
    EXPECT_TRUE(m.contains(1));
    EXPECT_TRUE(m.contains(3));
    EXPECT_TRUE(m.contains(4));
    EXPECT_TRUE(m.contains(5));
    EXPECT_TRUE(m.contains(6));
    EXPECT_TRUE(m.contains(7));
}

TEST(MapTest, Erase_Node_With_Left_Child_Only_At_Root) {
    S21::map<int, std::string> m;
    // Создаем ситуацию, когда корневой узел имеет только левого потомка
    m.insert({2, "two"});
    m.insert({1, "one"});
    
    auto it = m.find(2); // корневой узел с левым потомком
    m.erase(it);
    
    EXPECT_EQ(m.size(), 1);
    EXPECT_FALSE(m.contains(2));
    EXPECT_TRUE(m.contains(1));
}

TEST(MapTest, Erase_Node_With_Left_Child_Only_Deep) {
    S21::map<int, std::string> m;
    // Создаем глубокую структуру с узлом, имеющим только левого потомка
    m.insert({8, "eight"});
    m.insert({4, "four"});
    m.insert({12, "twelve"});
    m.insert({2, "two"});
    m.insert({6, "six"});
    m.insert({10, "ten"});
    m.insert({14, "fourteen"});
    m.insert({1, "one"}); // Добавляем левого потомка для узла 2
    
    auto it = m.find(2); // узел с левым потомком
    m.erase(it);
    
    EXPECT_EQ(m.size(), 7);
    EXPECT_FALSE(m.contains(2));
    EXPECT_TRUE(m.contains(1));
    EXPECT_TRUE(m.contains(4));
    EXPECT_TRUE(m.contains(6));
    EXPECT_TRUE(m.contains(8));
    EXPECT_TRUE(m.contains(10));
    EXPECT_TRUE(m.contains(12));
    EXPECT_TRUE(m.contains(14));
}

TEST(MapTest, Erase_Node_With_Left_Child_Only_Multiple) {
    S21::map<int, std::string> m;
    // Создаем структуру с несколькими узлами, имеющими только левых потомков
    m.insert({5, "five"});
    m.insert({3, "three"});
    m.insert({2, "two"});
    m.insert({1, "one"});
    
    // Удаляем узел 3 (имеет только левого потомка 2)
    auto it = m.find(3);
    m.erase(it);
    
    EXPECT_EQ(m.size(), 3);
    EXPECT_FALSE(m.contains(3));
    EXPECT_TRUE(m.contains(1));
    EXPECT_TRUE(m.contains(2));
    EXPECT_TRUE(m.contains(5));
    
    // Удаляем узел 2 (имеет только левого потомка 1)
    it = m.find(2);
    m.erase(it);
    
    EXPECT_EQ(m.size(), 2);
    EXPECT_FALSE(m.contains(2));
    EXPECT_TRUE(m.contains(1));
    EXPECT_TRUE(m.contains(5));
}

TEST(MapTest, Iterator_Pre_Decrement) {
    S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto it = m.end();
    --it;
    
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, "three");
    it->second = "three_modified";
    EXPECT_EQ(it->second, "three_modified");
    
    --it;
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, "two");
    it->second = "two_modified";
    EXPECT_EQ(it->second, "two_modified");
}

TEST(MapTest, Iterator_Post_Decrement) {
    S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto it = m.end();
    auto old_it = it--;
    
    EXPECT_EQ(old_it, m.end());
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, "three");
    it->second = "three_modified";
    EXPECT_EQ(it->second, "three_modified");
    
    old_it = it--;
    EXPECT_EQ(old_it->first, 3);
    EXPECT_EQ(old_it->second, "three_modified");
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, "two");
    it->second = "two_modified";
    EXPECT_EQ(it->second, "two_modified");
}

TEST(MapTest, Iterator_Decrement_From_Begin) {
    S21::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    auto it = m.begin();
    --it;
    EXPECT_EQ(it, m.end());
}

TEST(MapTest, Iterator_Decrement_Empty) {
    S21::map<int, std::string> m;
    auto it = m.begin();
    --it;
    EXPECT_EQ(it, m.end());
}

TEST(MapTest, Iterator_Decrement_Modify_Values) {
    S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto it = m.end();
    --it;
    it->second = "modified_three";
    --it;
    it->second = "modified_two";
    --it;
    it->second = "modified_one";
    
    EXPECT_EQ(m[1], "modified_one");
    EXPECT_EQ(m[2], "modified_two");
    EXPECT_EQ(m[3], "modified_three");
}

TEST(MapTest, Const_Iterator_Post_Increment_Basic) {
    const S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto it = m.begin();
    auto old_it = it++;
    
    EXPECT_EQ(old_it->first, 1);
    EXPECT_EQ(old_it->second, "one");
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, "two");
}

TEST(MapTest, Const_Iterator_Post_Increment_To_End) {
    const S21::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    auto it = m.begin();
    auto old_it = it++;
    
    EXPECT_EQ(old_it->first, 1);
    EXPECT_EQ(old_it->second, "one");
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, "two");
    
    old_it = it++;
    EXPECT_EQ(old_it->first, 2);
    EXPECT_EQ(old_it->second, "two");
    EXPECT_EQ(it, m.end());
}

TEST(MapTest, Const_Iterator_Post_Increment_Empty) {
    const S21::map<int, std::string> m;
    auto it = m.begin();
    auto old_it = it++;
    
    EXPECT_EQ(old_it, m.begin());
    EXPECT_EQ(it, m.end());
}

TEST(MapTest, Const_Iterator_Post_Increment_Single_Element) {
    const S21::map<int, std::string> m = {{1, "one"}};
    auto it = m.begin();
    auto old_it = it++;
    
    EXPECT_EQ(old_it->first, 1);
    EXPECT_EQ(old_it->second, "one");
    EXPECT_EQ(it, m.end());
}

TEST(MapTest, Const_Iterator_Post_Increment_Sequence) {
    const S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
    auto it = m.begin();
    
    auto it1 = it++;
    EXPECT_EQ(it1->first, 1);
    EXPECT_EQ(it->first, 2);
    
    auto it2 = it++;
    EXPECT_EQ(it2->first, 2);
    EXPECT_EQ(it->first, 3);
    
    auto it3 = it++;
    EXPECT_EQ(it3->first, 3);
    EXPECT_EQ(it->first, 4);
    
    auto it4 = it++;
    EXPECT_EQ(it4->first, 4);
    EXPECT_EQ(it, m.end());
}

TEST(MapTest, Const_Iterator_Post_Decrement_Basic) {
    const S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto it = m.end();
    auto old_it = it--;
    
    EXPECT_EQ(old_it, m.end());
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, "three");
}

TEST(MapTest, Const_Iterator_Post_Decrement_Sequence) {
    const S21::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
    auto it = m.end();
    
    auto it1 = it--;
    EXPECT_EQ(it1, m.end());
    EXPECT_EQ(it->first, 4);
    EXPECT_EQ(it->second, "four");
    
    auto it2 = it--;
    EXPECT_EQ(it2->first, 4);
    EXPECT_EQ(it2->second, "four");
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, "three");
    
    auto it3 = it--;
    EXPECT_EQ(it3->first, 3);
    EXPECT_EQ(it3->second, "three");
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, "two");
    
    auto it4 = it--;
    EXPECT_EQ(it4->first, 2);
    EXPECT_EQ(it4->second, "two");
    EXPECT_EQ(it->first, 1);
    EXPECT_EQ(it->second, "one");
}

TEST(MapTest, Const_Iterator_Post_Decrement_From_Begin) {
    const S21::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    auto it = m.begin();
    auto old_it = it--;
    
    EXPECT_EQ(old_it->first, 1);
    EXPECT_EQ(old_it->second, "one");
    EXPECT_EQ(it, m.end());
}


TEST(MapTest, Const_Iterator_Post_Decrement_Empty) {
    const S21::map<int, std::string> m;
    auto it = m.begin();
    auto old_it = it--;
    
    EXPECT_EQ(old_it, m.begin());
    EXPECT_EQ(it, m.end());
}

TEST(MapTest, Fix_Delete_Red_Sibling) {
    S21::map<int, std::string> m;
    // Создаем структуру, где у удаляемого узла будет красный брат
    m.insert({5, "five"});
    m.insert({3, "three"});
    m.insert({7, "seven"});
    m.insert({2, "two"});
    m.insert({4, "four"});
    m.insert({6, "six"});
    m.insert({8, "eight"});
    
    // Удаляем узел 2 (черный лист)
    auto it = m.find(2);
    m.erase(it);
    
    // Проверяем, что дерево остается сбалансированным
    EXPECT_EQ(m.size(), 6);
    EXPECT_FALSE(m.contains(2));
    EXPECT_TRUE(m.contains(3));
    EXPECT_TRUE(m.contains(4));
    EXPECT_TRUE(m.contains(5));
    EXPECT_TRUE(m.contains(6));
    EXPECT_TRUE(m.contains(7));
    EXPECT_TRUE(m.contains(8));
}

TEST(MapTest, Fix_Delete_Black_Sibling_With_Black_Children) {
    S21::map<int, std::string> m;
    // Создаем структуру, где у удаляемого узла будет черный брат с черными детьми
    m.insert({5, "five"});
    m.insert({3, "three"});
    m.insert({7, "seven"});
    m.insert({2, "two"});
    m.insert({4, "four"});
    m.insert({6, "six"});
    m.insert({8, "eight"});
    
    // Удаляем узел 4 (черный лист)
    auto it = m.find(4);
    m.erase(it);
    
    // Проверяем, что дерево остается сбалансированным
    EXPECT_EQ(m.size(), 6);
    EXPECT_FALSE(m.contains(4));
    EXPECT_TRUE(m.contains(2));
    EXPECT_TRUE(m.contains(3));
    EXPECT_TRUE(m.contains(5));
    EXPECT_TRUE(m.contains(6));
    EXPECT_TRUE(m.contains(7));
    EXPECT_TRUE(m.contains(8));
}

TEST(MapTest, Fix_Delete_Black_Sibling_With_Red_Left_Child) {
    S21::map<int, std::string> m;
    
    // Создаем структуру, где у удаляемого узла будет черный брат
    // с красным левым ребенком и черным правым ребенком
    m.insert({10, "ten"});     // черный корень
    m.insert({5, "five"});     // красный левый ребенок
    m.insert({15, "fifteen"}); // черный правый ребенок
    m.insert({3, "three"});    // черный левый ребенок
    m.insert({7, "seven"});    // черный правый ребенок
    m.insert({12, "twelve"});  // красный левый ребенок
    m.insert({17, "seventeen"}); // черный правый ребенок
    
    // Принудительно устанавливаем цвета
    auto it10 = m.find(10);
    auto it5 = m.find(5);
    auto it15 = m.find(15);
    auto it3 = m.find(3);
    auto it7 = m.find(7);
    auto it12 = m.find(12);
    auto it17 = m.find(17);
    
    if (it10 != m.end()) it10.getCurrent()->is_black = true;
    if (it5 != m.end()) it5.getCurrent()->is_black = false;
    if (it15 != m.end()) it15.getCurrent()->is_black = true;
    if (it3 != m.end()) it3.getCurrent()->is_black = true;
    if (it7 != m.end()) it7.getCurrent()->is_black = true;
    if (it12 != m.end()) it12.getCurrent()->is_black = false;
    if (it17 != m.end()) it17.getCurrent()->is_black = true;
    
    // Выводим структуру дерева до удаления
    std::cout << "Tree structure before deletion:" << std::endl;
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << "Key: " << it->first << ", Color: " << (it.getCurrent()->is_black ? "black" : "red") << std::endl;
    }
    
    // Удаляем узел 3 (черный лист)
    m.erase(it3);
    
    // Выводим структуру дерева после удаления
    std::cout << "Tree structure after deletion:" << std::endl;
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << "Key: " << it->first << ", Color: " << (it.getCurrent()->is_black ? "black" : "red") << std::endl;
    }
    
    // Проверяем, что дерево остается сбалансированным
    EXPECT_EQ(m.size(), 6);
    EXPECT_FALSE(m.contains(3));
    
    // Проверяем, что все остальные элементы доступны
    EXPECT_TRUE(m.contains(5));
    EXPECT_TRUE(m.contains(7));
    EXPECT_TRUE(m.contains(10));
    EXPECT_TRUE(m.contains(12));
    EXPECT_TRUE(m.contains(15));
    EXPECT_TRUE(m.contains(17));
    
    // Проверяем, что структура дерева корректна после удаления
    it5 = m.find(5);
    it7 = m.find(7);
    it10 = m.find(10);
    it15 = m.find(15);
    it12 = m.find(12);
    it17 = m.find(17);
    
    // Проверяем связи между узлами
    EXPECT_NE(it5, m.end());
    EXPECT_NE(it7, m.end());
    EXPECT_NE(it10, m.end());
    EXPECT_NE(it15, m.end());
    EXPECT_NE(it12, m.end());
    EXPECT_NE(it17, m.end());
    
    // Проверяем, что порядок элементов сохранился
    std::vector<int> expected_order = {5, 7, 10, 12, 15, 17};
    std::vector<int> actual_order;
    for (auto it = m.begin(); it != m.end(); ++it) {
        actual_order.push_back(it->first);
    }
    EXPECT_EQ(actual_order, expected_order);
}

TEST(MapTest, Fix_Delete_Black_Sibling_With_Red_Right_Child) {
    S21::map<int, std::string> m;
    // Создаем структуру, где у удаляемого узла будет черный брат с красным правым ребенком
    m.insert({5, "five"});
    m.insert({3, "three"});
    m.insert({7, "seven"});
    m.insert({2, "two"});
    m.insert({4, "four"});
    m.insert({6, "six"});
    m.insert({8, "eight"});
    m.insert({9, "nine"}); // Добавляем красного правого ребенка для узла 8
    
    // Удаляем узел 6 (черный лист)
    auto it = m.find(6);
    m.erase(it);
    
    // Проверяем, что дерево остается сбалансированным
    EXPECT_EQ(m.size(), 7);
    EXPECT_FALSE(m.contains(6));
    EXPECT_TRUE(m.contains(2));
    EXPECT_TRUE(m.contains(3));
    EXPECT_TRUE(m.contains(4));
    EXPECT_TRUE(m.contains(5));
    EXPECT_TRUE(m.contains(7));
    EXPECT_TRUE(m.contains(8));
    EXPECT_TRUE(m.contains(9));
}

TEST(MapTest, Fix_Delete_Complex_Case) {
    S21::map<int, std::string> m;
    // Создаем сложную структуру для проверки всех случаев
    m.insert({10, "ten"});
    m.insert({5, "five"});
    m.insert({15, "fifteen"});
    m.insert({3, "three"});
    m.insert({7, "seven"});
    m.insert({12, "twelve"});
    m.insert({17, "seventeen"});
    m.insert({2, "two"});
    m.insert({4, "four"});
    m.insert({6, "six"});
    m.insert({8, "eight"});
    m.insert({11, "eleven"});
    m.insert({13, "thirteen"});
    m.insert({16, "sixteen"});
    m.insert({18, "eighteen"});
    
    // Удаляем несколько узлов, чтобы проверить разные случаи
    auto it = m.find(2);
    m.erase(it);
    
    it = m.find(4);
    m.erase(it);
    
    it = m.find(6);
    m.erase(it);
    
    it = m.find(8);
    m.erase(it);
    
    // Проверяем, что дерево остается сбалансированным
    EXPECT_EQ(m.size(), 11);
    EXPECT_FALSE(m.contains(2));
    EXPECT_FALSE(m.contains(4));
    EXPECT_FALSE(m.contains(6));
    EXPECT_FALSE(m.contains(8));
    EXPECT_TRUE(m.contains(3));
    EXPECT_TRUE(m.contains(5));
    EXPECT_TRUE(m.contains(7));
    EXPECT_TRUE(m.contains(10));
    EXPECT_TRUE(m.contains(11));
    EXPECT_TRUE(m.contains(12));
    EXPECT_TRUE(m.contains(13));
    EXPECT_TRUE(m.contains(15));
    EXPECT_TRUE(m.contains(16));
    EXPECT_TRUE(m.contains(17));
    EXPECT_TRUE(m.contains(18));
}

TEST(MapTest, Fix_Delete_Red_Sibling_Detailed) {
    S21::map<int, std::string> m;
    
    // Создаем структуру, где у удаляемого узла будет красный брат
    m.insert({10, "ten"});     // черный корень
    m.insert({5, "five"});     // красный левый ребенок
    m.insert({15, "fifteen"}); // черный правый ребенок
    m.insert({3, "three"});    // черный левый ребенок
    m.insert({7, "seven"});    // черный правый ребенок
    m.insert({12, "twelve"});  // красный левый ребенок
    m.insert({17, "seventeen"}); // черный правый ребенок
    
    // Принудительно устанавливаем цвета
    auto it10 = m.find(10);
    auto it5 = m.find(5);
    auto it15 = m.find(15);
    auto it3 = m.find(3);
    auto it7 = m.find(7);
    auto it12 = m.find(12);
    auto it17 = m.find(17);
    
    if (it10 != m.end()) it10.getCurrent()->is_black = true;
    if (it5 != m.end()) it5.getCurrent()->is_black = false;
    if (it15 != m.end()) it15.getCurrent()->is_black = true;
    if (it3 != m.end()) it3.getCurrent()->is_black = true;
    if (it7 != m.end()) it7.getCurrent()->is_black = true;
    if (it12 != m.end()) it12.getCurrent()->is_black = false;
    if (it17 != m.end()) it17.getCurrent()->is_black = true;
    
    // Выводим структуру дерева до удаления
    std::cout << "Tree structure before deletion:" << std::endl;
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << "Key: " << it->first << ", Color: " << (it.getCurrent()->is_black ? "black" : "red") << std::endl;
    }
    
    // Удаляем узел 3 (черный лист)
    m.erase(it3);
    
    // Выводим структуру дерева после удаления
    std::cout << "Tree structure after deletion:" << std::endl;
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << "Key: " << it->first << ", Color: " << (it.getCurrent()->is_black ? "black" : "red") << std::endl;
    }
    
    // Проверяем, что дерево остается сбалансированным
    EXPECT_EQ(m.size(), 6);
    EXPECT_FALSE(m.contains(3));
    
    // Проверяем, что все остальные элементы доступны
    EXPECT_TRUE(m.contains(5));
    EXPECT_TRUE(m.contains(7));
    EXPECT_TRUE(m.contains(10));
    EXPECT_TRUE(m.contains(12));
    EXPECT_TRUE(m.contains(15));
    EXPECT_TRUE(m.contains(17));
    
    // Проверяем, что структура дерева корректна после удаления
    it5 = m.find(5);
    it7 = m.find(7);
    it10 = m.find(10);
    it15 = m.find(15);
    it12 = m.find(12);
    it17 = m.find(17);
    
    // Проверяем связи между узлами
    EXPECT_NE(it5, m.end());
    EXPECT_NE(it7, m.end());
    EXPECT_NE(it10, m.end());
    EXPECT_NE(it15, m.end());
    EXPECT_NE(it12, m.end());
    EXPECT_NE(it17, m.end());
    
    // Проверяем, что порядок элементов сохранился
    std::vector<int> expected_order = {5, 7, 10, 12, 15, 17};
    std::vector<int> actual_order;
    for (auto it = m.begin(); it != m.end(); ++it) {
        actual_order.push_back(it->first);
    }
    EXPECT_EQ(actual_order, expected_order);
}

