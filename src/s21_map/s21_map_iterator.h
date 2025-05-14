#ifndef S21_MAP_ITERATOR_H
#define S21_MAP_ITERATOR_H

namespace s21 {

template <typename Key, typename T>
class map<Key, T>::MapIterator {
 public:
  MapIterator();
  MapIterator(Node* node, Node* root);

  value_type& operator*();
  value_type* operator->();

  MapIterator& operator++();
  MapIterator operator++(int);
  MapIterator& operator--();

  MapIterator operator--(int);

  bool operator==(const MapIterator& other) const;

  bool operator!=(const MapIterator& other) const;
  Node* getCurrent() const;

 private:
  Node* current_;
  Node* root_;
};

template <typename Key, typename T>
class map<Key, T>::MapConstIterator {
 public:
  MapConstIterator();
  explicit MapConstIterator(Node* node, Node* root);

  const value_type& operator*() const;
  const value_type* operator->() const;

  MapConstIterator& operator++();

  MapConstIterator operator++(int);

  MapConstIterator& operator--();

  MapConstIterator operator--(int);

  bool operator==(const MapConstIterator& other) const;

  bool operator!=(const MapConstIterator& other) const;

  Node* getCurrent() const;

 private:
  Node* current_;
  Node* root_;
};

}  // namespace s21

#include "s21_map_iterator.tpp"

#endif  // S21_MAP_ITERATOR_H