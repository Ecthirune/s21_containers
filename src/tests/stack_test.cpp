#include <gtest/gtest.h>
#include <initializer_list>
#include "../s21_stack/s21_stack.h" 

namespace s21 {

class StackTest : public ::testing::Test {
protected:
    using IntStack = stack<int>;
    IntStack empty_stack;
    IntStack stack_with_elements{1, 2, 3};
};

TEST_F(StackTest, DefaultConstructor) {
    EXPECT_TRUE(empty_stack.empty());
    EXPECT_EQ(empty_stack.size(), 0u);
}

TEST_F(StackTest, InitializerListConstructor) {
    EXPECT_FALSE(stack_with_elements.empty());
    EXPECT_EQ(stack_with_elements.size(), 3u);
    EXPECT_EQ(stack_with_elements.top(), 3);
}

TEST_F(StackTest, CopyConstructor) {
    IntStack copy_stack(stack_with_elements);
    EXPECT_EQ(copy_stack.size(), stack_with_elements.size());
    EXPECT_EQ(copy_stack.top(), stack_with_elements.top());
    copy_stack.pop();
    EXPECT_EQ(copy_stack.size(), 2u);
    EXPECT_EQ(stack_with_elements.size(), 3u); 
}

TEST_F(StackTest, MoveConstructor) {
    IntStack temp_stack{1, 2, 3};
    IntStack moved_stack(std::move(temp_stack));
    EXPECT_EQ(moved_stack.size(), 3u);
    EXPECT_EQ(moved_stack.top(), 3);
    EXPECT_TRUE(temp_stack.empty()); 
}

TEST_F(StackTest, MoveAssignmentOperator) {
    IntStack temp_stack{1, 2, 3};
    empty_stack = std::move(temp_stack);
    EXPECT_EQ(empty_stack.size(), 3u);
    EXPECT_EQ(empty_stack.top(), 3);
    EXPECT_TRUE(temp_stack.empty());
}

TEST_F(StackTest, MoveAssignmentOperatorSelf) {
    IntStack temp_stack{1, 2, 3};
    temp_stack = std::move(temp_stack); 
    EXPECT_EQ(temp_stack.size(), 3u);
    EXPECT_EQ(temp_stack.top(), 3);
}

TEST_F(StackTest, Top) {
    EXPECT_EQ(stack_with_elements.top(), 3);
    const IntStack const_stack{1, 2, 3};
    EXPECT_EQ(const_stack.top(), 3);
}

TEST_F(StackTest, Empty) {
    EXPECT_TRUE(empty_stack.empty());
    EXPECT_FALSE(stack_with_elements.empty());
}

TEST_F(StackTest, Size) {
    EXPECT_EQ(empty_stack.size(), 0u);
    EXPECT_EQ(stack_with_elements.size(), 3u);
}

TEST_F(StackTest, Push) {
    empty_stack.push(42);
    EXPECT_EQ(empty_stack.size(), 1u);
    EXPECT_EQ(empty_stack.top(), 42);
    empty_stack.push(43);
    EXPECT_EQ(empty_stack.size(), 2u);
    EXPECT_EQ(empty_stack.top(), 43);
}

TEST_F(StackTest, Pop) {
    stack_with_elements.pop();
    EXPECT_EQ(stack_with_elements.size(), 2u);
    EXPECT_EQ(stack_with_elements.top(), 2);
    stack_with_elements.pop();
    EXPECT_EQ(stack_with_elements.size(), 1u);
    EXPECT_EQ(stack_with_elements.top(), 1);
}

TEST_F(StackTest, Swap) {
    IntStack other_stack{4, 5};
    stack_with_elements.swap(other_stack);
    EXPECT_EQ(stack_with_elements.size(), 2u);
    EXPECT_EQ(stack_with_elements.top(), 5);
    EXPECT_EQ(other_stack.size(), 3u);
    EXPECT_EQ(other_stack.top(), 3);
}

TEST_F(StackTest, PushPopSequence) {
    empty_stack.push(1);
    empty_stack.push(2);
    empty_stack.push(3);
    EXPECT_EQ(empty_stack.size(), 3u);
    EXPECT_EQ(empty_stack.top(), 3);
    empty_stack.pop();
    EXPECT_EQ(empty_stack.top(), 2);
    empty_stack.pop();
    EXPECT_EQ(empty_stack.top(), 1);
    empty_stack.pop();
    EXPECT_TRUE(empty_stack.empty());
}

TEST_F(StackTest, StringStack) {
    stack<std::string> str_stack;
    str_stack.push("first");
    str_stack.push("second");
    EXPECT_EQ(str_stack.size(), 2u);
    EXPECT_EQ(str_stack.top(), "second");
    str_stack.pop();
    EXPECT_EQ(str_stack.top(), "first");
}

} // namespace s21

