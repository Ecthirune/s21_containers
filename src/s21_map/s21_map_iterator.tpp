#ifndef S21_MAP_ITERATOR_TPP
#define S21_MAP_ITERATOR_TPP

namespace s21 {
template <typename Key, typename T>
map<Key, T>::MapIterator::MapIterator() : current_(nullptr), root_(nullptr){};

template <typename Key, typename T>
map<Key, T>::MapIterator::MapIterator(Node* node, Node* root)
    : current_(node), root_(root){};

template <typename Key, typename T>
typename map<Key, T>::value_type& map<Key, T>::MapIterator::operator*() {
  return current_->data;
};

template <typename Key, typename T>
typename map<Key, T>::value_type* map<Key, T>::MapIterator::operator->() {
  return &(current_->data);
}

template <typename Key, typename T>
typename map<Key, T>::MapIterator& map<Key, T>::MapIterator::operator++() {
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
};

template <typename Key, typename T>
typename map<Key, T>::MapIterator map<Key, T>::MapIterator::operator++(int) {
  MapIterator temp = *this;
  ++(*this);
  return temp;
};

template <typename Key, typename T>
typename map<Key, T>::MapIterator& map<Key, T>::MapIterator::operator--() {
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
};

template <typename Key, typename T>
typename map<Key, T>::MapIterator map<Key, T>::MapIterator::operator--(int) {
  MapIterator temp = *this;
  --(*this);
  return temp;
};

template <typename Key, typename T>
bool map<Key, T>::MapIterator::operator==(const MapIterator& other) const {
  return current_ == other.current_;
};

template <typename Key, typename T>
bool map<Key, T>::MapIterator::operator!=(const MapIterator& other) const {
  return current_ != other.current_;
};

template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::MapIterator::getCurrent() const {
  return current_;
};

template <typename Key, typename T>
map<Key, T>::MapConstIterator::MapConstIterator()
    : current_(nil_), root_(nullptr){};

template <typename Key, typename T>
map<Key, T>::MapConstIterator::MapConstIterator(Node* node, Node* root)
    : current_(node), root_(root){};

template <typename Key, typename T>
const typename map<Key, T>::value_type&
map<Key, T>::MapConstIterator::operator*() const {
  return current_->data;
};

template <typename Key, typename T>
const typename map<Key, T>::value_type*
map<Key, T>::MapConstIterator::operator->() const {
  return &(current_->data);
};

template <typename Key, typename T>
typename map<Key, T>::MapConstIterator&
map<Key, T>::MapConstIterator::operator++() {
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

template <typename Key, typename T>
typename map<Key, T>::MapConstIterator
map<Key, T>::MapConstIterator::operator++(int) {
  MapConstIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key, typename T>
typename map<Key, T>::MapConstIterator&
map<Key, T>::MapConstIterator::operator--() {
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
};

template <typename Key, typename T>
typename map<Key, T>::MapConstIterator
map<Key, T>::MapConstIterator::operator--(int) {
  MapConstIterator temp = *this;
  --(*this);
  return temp;
};

template <typename Key, typename T>
bool map<Key, T>::MapConstIterator::operator==(
    const MapConstIterator& other) const {
  return current_ == other.current_;
}

template <typename Key, typename T>
bool map<Key, T>::MapConstIterator::operator!=(
    const MapConstIterator& other) const {
  return current_ != other.current_;
}

template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::MapConstIterator::getCurrent() const {
  return current_;
};




}  // namespace s21

#endif  // S21_MAP_ITERATOR_TPP