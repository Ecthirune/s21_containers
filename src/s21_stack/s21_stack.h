#include "../s21_vector/s21_vector.h"


namespace s21 {
    template <typename T, typename Container = s21::vector<T>> 
    class stack {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

    // Конструкторы
    stack( ) : container_() {};
    explicit stack(std::initializer_list<value_type> const& items) : container_(items) {}
    stack(const stack& s) : container_(s.container_) {}
    stack(stack&& s) noexcept : container_(std::move(s.container_)) {}
    ~stack() = default;

    // Оператор присваивания
    stack& operator=(stack&& s) noexcept {
        if (this != &s) {
            container_ =(std::move(s.container_));
        }
        return *this;
    }

    // Основные методы стека
    reference top() {
        return container_.back();
    }
    const_reference top() const {
        return container_.back();
    }
    bool empty() const {
        return container_.empty();
    }
    size_type size() const {
        return container_.size();
    }
    void push(const_reference value) {
        container_.push_back(value); 
    }
    void pop() {
        container_.pop_back(); 
    }
    void swap(stack& other) {
        container_.swap(other.container_);
    }
    private:
        Container container_;
};
} // namespace s21