#include "../s21_vector/s21_vector.h"


namespace s21 {
template <typename T>
class stack : public s21::vector<T> {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

    // Конструкторы
    stack() : s21::vector<T>() {}
    stack(std::initializer_list<value_type> const& items) : s21::vector<T>(items) {}
    stack(const stack& s) : s21::vector<T>(s) {}
    stack(stack&& s) noexcept : s21::vector<T>(std::move(s)) {}
    ~stack() = default;

    // Оператор присваивания
    stack& operator=(stack&& s) noexcept {
        if (this != &s) {
            s21::vector<T>::operator=(std::move(s));
        }
        return *this;
    }

    // Основные методы стека
    reference top() {
        return this->back();
    }
    const_reference top() const {
        return this->back();
    }
    bool empty() const {
        return s21::vector<T>::empty(); 
    }
    size_type size() const {
        return s21::vector<T>::size();
    }
    void push(const_reference value) {
        this->push_back(value); 
    }
    void pop() {
        this->pop_back(); 
    }
    void swap(stack& other) {
        s21::vector<T>::swap(other);
    }
};
} // namespace s21