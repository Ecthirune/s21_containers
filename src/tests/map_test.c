#include <gtest/gtest.h>
#include "../s21_map/s21_map.h"

TEST(MapTest, Default_constructor) {
    s21::map<int, int> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, Initializer_list_constructor) {
    s21::map<int, int> m{{1, 1}, {2, 2}, {3, 3}};
    EXPECT_EQ(m.size(), 3);
    EXPECT_FALSE(m.empty());
}

TEST(MapTest, Copy_constructor) {
    s21::map<int, int> m1{{1, 1}, {2, 2}, {3, 3}};
    s21::map<int, int> m2(m1);
    EXPECT_EQ(m1.size(), m2.size());
    EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(MapTest, Move_constructor) {
    s21::map<int, int> m1{{1, 1}, {2, 2}, {3, 3}};
    s21::map<int, int> m2(std::move(m1));
    EXPECT_EQ(m2.size(), 3);
    EXPECT_TRUE(m1.empty());
}

TEST(MapTest, Assignment_operator) {
    s21::map<int, int> m1{{1, 1}, {2, 2}, {3, 3}};
    s21::map<int, int> m2;
    m2 = m1;
    EXPECT_EQ(m1.size(), m2.size());
    EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(MapTest, Max_size) {
    s21::map<int, int> m;
    EXPECT_GT(m.max_size(), 0);
}

TEST(MapTest, Insert) {
    s21::map<int, int> m;
    auto [it, success] = m.insert({1, 1});
    EXPECT_TRUE(success);
    EXPECT_EQ(m.size(), 1);
    
    auto [it2, success2] = m.insert({1, 2}); // Попытка вставить существующий ключ
    EXPECT_FALSE(success2);
    EXPECT_EQ(m.size(), 1);
}

TEST(MapTest, Multiple_insert) {
    s21::map<int, int> m;
    std::vector<std::pair<int, int>> values = {
        {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}
    };
    int x = 0;
    for (const auto& value : values) {
        auto [it, success] = m.insert(value);
        EXPECT_TRUE(success);
        EXPECT_EQ(m.size(), ++x);
    }
}

TEST(MapTest, Multiple_insert2) {
    s21::map<int, int> m;
    std::vector<int> keys = {5, 3, 7, 1, 9, 4, 6, 2, 8, 0};
    
    for (int key : keys) {
        m.insert({key, key});
    }
    
    EXPECT_EQ(m.size(), keys.size());
    EXPECT_FALSE(m.empty());
}

TEST(MapTest, Complex_insert) {
    s21::map<std::string, int> m;
    std::vector<std::pair<std::string, int>> values = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5}
    };
    
    for (const auto& value : values) {
        auto [it, success] = m.insert(value);
        EXPECT_TRUE(success);
    }
    
    EXPECT_EQ(m.size(), values.size());
}

TEST(MapTest, Empty_map) {
    s21::map<int, int> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
    EXPECT_GT(m.max_size(), 0);
}

TEST(MapTest, Large_insert) {
    s21::map<int, int> m;
    const int count = 1000;
    
    for (int i = 0; i < count; ++i) {
        auto [it, success] = m.insert({i, i});
        EXPECT_TRUE(success);
        EXPECT_EQ(m.size(), i + 1);
    }
    
    EXPECT_EQ(m.size(), count);
}

TEST(MapTest, Insert_or_assign) {
    s21::map<int, int> m;
    
    /* Тест вставки нового элемента */
    auto [it1, success1] = m.insert_or_assign(1, 1);
    EXPECT_TRUE(success1);
    EXPECT_EQ(m.size(), 1);
    
    /* Тест обновления существующего элемента */
    auto [it2, success2] = m.insert_or_assign(1, 2);
    EXPECT_FALSE(success2);
    EXPECT_EQ(m.size(), 1);
    EXPECT_EQ(it2->second, 2);
    
    /* Тест вставки нескольких элементов */
    m.insert_or_assign(2, 2);
    m.insert_or_assign(3, 3);
    EXPECT_EQ(m.size(), 3);
}

TEST(MapTest, Find) {
    s21::map<int, int> m{{1, 1}, {2, 2}, {3, 3}};
    
    /* Тест поиска существующего элемента */
    auto it1 = m.find(2);
    EXPECT_NE(it1, m.end());
    EXPECT_EQ(it1->second, 2);
    
    /* Тест поиска несуществующего элемента */
    auto it2 = m.find(4);
    EXPECT_EQ(it2, m.end());
    
    /* Тест поиска в пустом map */
    s21::map<int, int> empty_m;
    auto it3 = empty_m.find(1);
    EXPECT_EQ(it3, empty_m.end());
}

TEST(MapTest, Find_const) {
    const s21::map<int, int> m{{1, 1}, {2, 2}, {3, 3}};
    
    /* Тест поиска существующего элемента */
    auto it1 = m.find(2);
    EXPECT_NE(it1, m.end());
    EXPECT_EQ(it1->second, 2);
    
    /* Тест поиска несуществующего элемента */
    auto it2 = m.find(4);
    EXPECT_EQ(it2, m.end());
}

TEST(MapTest, Complex_insert_or_assign) {
    s21::map<std::string, int> m;
    
    /* Тест вставки строковых ключей */
    auto [it1, success1] = m.insert_or_assign("one", 1);
    EXPECT_TRUE(success1);
    EXPECT_EQ(m.size(), 1);
    
    /* Тест обновления значения */
    auto [it2, success2] = m.insert_or_assign("one", 2);
    EXPECT_FALSE(success2);
    EXPECT_EQ(it2->second, 2);
    
    /* Тест вставки нескольких элементов */
    m.insert_or_assign("two", 2);
    m.insert_or_assign("three", 3);
    EXPECT_EQ(m.size(), 3);
    
    /* Проверка значений */
    EXPECT_EQ(m.find("one")->second, 2);
    EXPECT_EQ(m.find("two")->second, 2);
    EXPECT_EQ(m.find("three")->second, 3);
}

TEST(MapTest, Find_after_balance) {
    s21::map<int, int> m;
    
    /* Вставляем элементы в порядке, требующем балансировки */
    std::vector<int> keys = {5, 3, 7, 1, 9, 4, 6, 2, 8, 0};
    
    for (int key : keys) {
        m.insert_or_assign(key, key);
    }
    
    /* Проверяем, что все элементы доступны после балансировки */
    for (int key : keys) {
        auto it = m.find(key);
        EXPECT_NE(it, m.end());
        EXPECT_EQ(it->second, key);
    }
}

TEST(MapTest, Iterator_operations) {
    s21::map<int, int> m{{1, 1}, {2, 2}, {3, 3}};
    
    /* Проверка begin() */
    auto it = m.begin();
    EXPECT_NE(it, m.end());
    EXPECT_EQ(it->first, 1);
    EXPECT_EQ(it->second, 1);
    
    /* Проверка оператора ++ */
    ++it;
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, 2);
    
    /* Проверка оператора -- */
    --it;
    EXPECT_EQ(it->first, 1);
    EXPECT_EQ(it->second, 1);
    
    /* Проверка оператора * */
    auto pair = *it;
    EXPECT_EQ(pair.first, 1);
    EXPECT_EQ(pair.second, 1);
}

TEST(MapTest, Iterator_comparison) {
    s21::map<int, int> m{{1, 1}, {2, 2}, {3, 3}};
    
    auto it1 = m.begin();
    auto it2 = m.begin();
    EXPECT_TRUE(it1 == it2);
    
    ++it1;
    EXPECT_FALSE(it1 == it2);
    
    auto end_it = m.end();
    EXPECT_NE(it1, end_it);
}

TEST(MapTest, Empty_map_iteration) {
    s21::map<int, int> m;
    
    auto begin = m.begin();
    auto end = m.end();
    
    EXPECT_EQ(begin, end);
}

TEST(MapTest, Iterator_traversal) {
    s21::map<int, int> m;
    std::vector<std::pair<int, int>> values = {
        {5, 5}, {3, 3}, {7, 7}, {1, 1}, {9, 9},
        {4, 4}, {6, 6}, {2, 2}, {8, 8}, {0, 0}
    };
    
    for (const auto& value : values) {
        m.insert(value);
    }
    
    /* Проверка прямого обхода */
    auto it = m.begin();
    std::vector<int> expected_keys = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < expected_keys.size(); ++i) {
        EXPECT_EQ(it->first, expected_keys[i]);
        EXPECT_EQ(it->second, expected_keys[i]);
        ++it;
    }
    EXPECT_EQ(it, m.end());
    
    /* Проверка обратного обхода */
    --it;
    for (int i = expected_keys.size() - 1; i >= 0; --i) {
        EXPECT_EQ(it->first, expected_keys[i]);
        EXPECT_EQ(it->second, expected_keys[i]);
        --it;
    }
}

TEST(MapTest, String_map_iteration) {
    s21::map<std::string, int> m;
    std::vector<std::pair<std::string, int>> values = {
        {"apple", 1},
        {"banana", 2},
        {"orange", 3},
        {"grape", 4}
    };
    
    for (const auto& value : values) {
        m.insert(value);
    }
    
    auto it = m.begin();
    EXPECT_EQ(it->first, "apple");
    EXPECT_EQ(it->second, 1);
    
    ++it;
    EXPECT_EQ(it->first, "banana");
    EXPECT_EQ(it->second, 2);
    
    ++it;
    EXPECT_EQ(it->first, "grape");
    EXPECT_EQ(it->second, 4);
    
    ++it;
    EXPECT_EQ(it->first, "orange");
    EXPECT_EQ(it->second, 3);
    
    ++it;
    EXPECT_EQ(it, m.end());
}

TEST(MapTest, Const_iterator) {
    const s21::map<int, int> m{{1, 1}, {2, 2}, {3, 3}};
    
    auto it = m.begin();
    EXPECT_EQ(it->first, 1);
    EXPECT_EQ(it->second, 1);
    
    ++it;
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, 2);
    
    auto end = m.end();
    EXPECT_NE(it, end);

}
