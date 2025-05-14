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
  class MapIterator {
   public:
    MapIterator() : current_(nullptr), root_(nullptr) {}
    explicit MapIterator(Node* node, Node* root)
        : current_(node), root_(root) {}

    value_type& operator*() { return current_->data; }
    value_type* operator->() { return &(current_->data); }

    MapIterator& operator++() {
      if (current_ == nil_) return *this;
      if (current_->right && current_->right != nil_) {
        current_ = current_->right;
        while (current_->left && current_->left != nil_) {
          current_ = current_->left;
        }
      } else {
        Node* parent = current_->parent;
        while (parent && current_ == parent->right) {
          current_ = parent;
          parent = parent->parent;
        }
        current_ = parent ? parent : nil_;
      }
      return *this;
    }

    MapIterator operator++(int) {
      MapIterator temp = *this;
      ++(*this);
      return temp;
    }

    MapIterator& operator--() {
      if (current_ == nil_) {
        // Если мы в end(), находим максимальный элемент
        Node* node = root_;
        if (node) {
          while (node->right && node->right != nil_) {
            node = node->right;
          }
          current_ = node;
        }
      } else if (current_->left && current_->left != nil_) {
        // Находим максимум в левом поддереве
        current_ = current_->left;
        while (current_->right && current_->right != nil_) {
          current_ = current_->right;
        }
      } else {
        // Идем вверх, пока не найдем узел, который является правым потомком
        Node* parent = current_->parent;
        while (parent && current_ == parent->left) {
          current_ = parent;
          parent = parent->parent;
        }
        current_ = parent ? parent : nil_;
      }
      return *this;
    }

    MapIterator operator--(int) {
      MapIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const MapIterator& other) const {
      return current_ == other.current_;
    }

    bool operator!=(const MapIterator& other) const {
      return current_ != other.current_;
    }

    Node* getCurrent() const { return current_; }

   private:
    Node* current_;
    Node* root_;
  };

  // Класс константного итератора
  class MapConstIterator {
   public:
    MapConstIterator() : current_(nil_), root_(nullptr) {}
    explicit MapConstIterator(Node* node, Node* root)
        : current_(node), root_(root) {}

    const value_type& operator*() const { return current_->data; }
    const value_type* operator->() const { return &(current_->data); }

    MapConstIterator& operator++() {
      if (current_ == nil_) return *this;
      if (current_->right && current_->right != nil_) {
        current_ = current_->right;
        while (current_->left && current_->left != nil_) {
          current_ = current_->left;
        }
      } else {
        Node* parent = current_->parent;
        while (parent && current_ == parent->right) {
          current_ = parent;
          parent = parent->parent;
        }
        current_ = parent ? parent : nil_;
      }
      return *this;
    }

    MapConstIterator operator++(int) {
      MapConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    MapConstIterator& operator--() {
      if (current_ == nil_) {
        // Если мы в end(), находим максимальный элемент
        Node* node = root_;
        if (node) {
          while (node->right && node->right != nil_) {
            node = node->right;
          }
          current_ = node;
        }
      } else if (current_->left && current_->left != nil_) {
        // Находим максимальный элемент в левом поддереве
        current_ = current_->left;
        while (current_->right && current_->right != nil_) {
          current_ = current_->right;
        }
      } else {
        // Идем вверх, пока не найдем узел, который является правым потомком
        Node* parent = current_->parent;
        while (parent && current_ == parent->left) {
          current_ = parent;
          parent = parent->parent;
        }
        current_ = parent ? parent : nil_;
      }
      return *this;
    }

    MapConstIterator operator--(int) {
      MapConstIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const MapConstIterator& other) const {
      return current_ == other.current_;
    }

    bool operator!=(const MapConstIterator& other) const {
      return current_ != other.current_;
    }

    Node* getCurrent() const { return current_; }

   private:
    Node* current_;
    Node* root_;
  };

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

#endif  // S21_MAP_H_
