#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  // Ренеймы
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  // Структура узла
  struct Node {
    value_type data;
    Node* left;
    Node* right;
    Node* parent;
    bool is_black;

    Node(const value_type& val, Node* p = nullptr, bool black = false)
        : data(val),
          left(nullptr),
          right(nullptr),
          parent(p),
          is_black(black) {}
  };

  // Класс итератора
  class MapConstIterator;
  class MapIterator;

  using iterator = MapIterator;
  using const_iterator = MapConstIterator;

  // Конструкторы
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  ~map();

  // Оператор присваивания
  map& operator=(map&& m);
  map& operator=(const map& m);

  // Доступ к элементам
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Итераторы
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // Вместимость
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Модификаторы
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  // Поиск

  iterator find(const Key& key);
  const_iterator find(const Key& key) const;

 private:
  Node* root_;
  size_type size_;
  static Node* nil_;  // Статический фейк узел для листовых узлов

  // Вспомогательные функции
  bool contains(const Key& key) const;
  void rotate_left(Node* x);
  void rotate_right(Node* x);
  void fix_insert(Node* z);
  void fix_delete(Node* x);
  Node* find_node(const Key& key) const;
  void clear_helper(Node* node);
  typename map<Key, T>::Node* copy_tree(Node* node, Node* parent);
  void transplant(Node* u, Node* v);
  typename map<Key, T>::Node* minimum(Node* node) const;
};

}  // namespace s21

#include "s21_map.tpp"
#include "s21_map_iterator.h"
#endif  // S21_MAP_H_
