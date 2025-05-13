#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>

namespace s21 {

template <typename T>
class list {
 private:
  struct Node {
    T value;
    Node* next = nullptr;
    Node* prev = nullptr;
    Node() : value(T()), next(nullptr), prev(nullptr){};
    Node(const T& val) : value(val), next(nullptr), prev(nullptr){};
  };
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_t size_ = 0;

 public:
  using value_type = T;

  using reference = T&;
  using const_reference = const T&;

  using iterator = Node*;
  using const_iterator = const Node*;

  using size_type = size_t;

 public:
  list();

  /* конструктор с параметром */
  list(size_type n);

  /* инциализация списка объектов */
  list(std::initializer_list<value_type> const& items);

  /* конструктор копирования */
  list(const list& l);

  /* конструктор перемещения */
  list(list&& l) noexcept;

  /* деструктор */
  ~list() { clear(); };

  /* конструктор присваивания */
  list& operator=(list&& l) noexcept;

  const_reference front() const noexcept;
  const_reference back() const noexcept;
  iterator begin() noexcept;
  iterator end() noexcept;
  bool empty() const noexcept;
  size_type size();
  size_type max_size() const noexcept;

  /* удаление списка */
  void clear();

  iterator insert(iterator pos, const_reference value);

  /* удаление элемента */
  void erase(iterator pos);

  /* добавление элемента в конец */
  void push_back(const_reference value) noexcept;

  /* удаление последнего элемента */
  void pop_back();

  /* добавление элемента в начало */
  void push_front(const_reference value);

  /* удаление первого элемента */
  void pop_front();

  /* смена данных местами */
  void swap(list& other) noexcept;

  /* склеивание двух листов */
  void merge(list& other) noexcept;

  /* перемещение данных из other на current pos */
  void splice(const_iterator pos, list& other) noexcept;

  /* инверсия листа */
  void reverse() noexcept;

  /* удаление повторяющихся элементов из листа */
  void unique() noexcept;

  /* сортировка списка */
  void sort();

  /* Операторы сравнения */
  bool operator==(const list& other) const noexcept;

  bool operator!=(const list& other) const noexcept;

  bool operator<(const list& other) const noexcept;
  bool operator>(const list& other) const noexcept;

  bool operator<=(const list& other) const noexcept;

  bool operator>=(const list& other) const noexcept { return !(*this < other); }

  /* Операторы инкремента и декремента */
  iterator& operator++() noexcept;

  iterator operator++(int) noexcept;

  iterator& operator--() noexcept;

  iterator operator--(int) noexcept;

  /* Операторы сложения и вычитания */
  list operator+(const list& other) const noexcept;

  list& operator+=(const list& other) noexcept;

  list operator-(const list& other) const noexcept;

  list& operator-=(const list& other) noexcept;
};

};  // namespace s21

#include "s21_list.tpp"

#endif  // S21_LIST_H