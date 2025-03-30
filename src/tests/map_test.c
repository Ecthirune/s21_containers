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
