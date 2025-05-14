#ifndef S21_MAP_TPP
#define S21_MAP_TPP
namespace s21 {

template <typename Key, typename T>
map<Key, T>::map() : root_(nullptr), size_(0){};

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<map<Key, T>::value_type> const& items)
    : root_(nullptr), size_(0) {
  for (const auto& item : items) {
    insert(item);
  }
}

// Инициализация статической фейк ноды
template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::nil_ = []() {
  Node* n = new Node(value_type(), nullptr, true);
  n->left = n;
  n->right = n;
  n->parent = n;
  return n;
}();

template <typename Key, typename T>
map<Key, T>::map(const map& m) : root_(nullptr), size_(0) {
  if (this != &m) {
    if (m.root_) {
      root_ = copy_tree(m.root_, nullptr);
      size_ = m.size_;
    }
  }
}

template <typename Key, typename T>
map<Key, T>::map(map&& m) : root_(m.root_), size_(m.size_) {
  m.root_ = nullptr;
  m.size_ = 0;
}

template <typename Key, typename T>
map<Key, T>::~map() {
  clear();
}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map&& m) {
  if (this != &m) {
    clear();
    root_ = m.root_;
    size_ = m.size_;
    m.root_ = nullptr;
    m.size_ = 0;
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(const map& m) {
  if (this != &m) {
    clear();  // Очищаем старое дерево
    if (m.root_) {
      root_ = copy_tree(m.root_, nullptr);
      size_ = m.size_;
    } else {
      root_ = nullptr;
      size_ = 0;
    }
  }
  return *this;
}

template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  Node* node = find_node(key);
  if (node == nullptr) {
    throw std::out_of_range("Key not found");
  }
  return node->data.second;
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  Node* node = find_node(key);
  if (node == nullptr) {
    auto result = insert(key, T());
    return result.first->second;
  }
  return node->data.second;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  if (root_ == nullptr) return iterator(nil_, root_);
  Node* node = root_;
  while (node->left && node->left != nil_) {
    node = node->left;
  }
  return iterator(node, root_);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  return iterator(nil_, root_);
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::begin() const {
  if (!root_) return const_iterator(nil_, root_);
  Node* node = root_;
  while (node->left && node->left != nil_) {
    node = node->left;
  }
  return const_iterator(node, root_);
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::end() const {
  return const_iterator(nil_, root_);
}

template <typename Key, typename T>
bool map<Key, T>::empty() const {
  return size_ == 0;
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() const {
  return size_;
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <typename Key, typename T>
void map<Key, T>::clear() {
  clear_helper(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename T>
void map<Key, T>::clear_helper(Node* node) {
  if (node == nullptr || node == nil_) return;
  clear_helper(node->left);
  clear_helper(node->right);
  delete node;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  Node* parent = nullptr;
  Node* current = root_;

  while (current != nullptr && current != nil_) {
    parent = current;
    if (value.first < current->data.first) {
      current = current->left;
    } else if (value.first > current->data.first) {
      current = current->right;
    } else {
      return std::make_pair(iterator(current, root_), false);
    }
  }

  Node* newNode = new Node(value, parent);
  if (parent == nullptr) {
    root_ = newNode;
  } else if (value.first < parent->data.first) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }

  newNode->left = nil_;
  newNode->right = nil_;
  newNode->is_black = false;
  size_++;

  fix_insert(newNode);
  return std::make_pair(iterator(newNode, root_), true);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  return insert(std::make_pair(key, obj));
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  auto result = insert(key, obj);
  if (!result.second) {
    result.first->second = obj;
  }
  return result;
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  if (pos == end()) return;

  Node* z = pos.getCurrent();
  Node* y = z;
  Node* x;
  bool y_original_color = y->is_black;

  if (z->left == nil_) {
    x = z->right;
    transplant(z, z->right);
  } else if (z->right == nil_) {
    x = z->left;
    transplant(z, z->left);
  } else {
    y = minimum(z->right);
    y_original_color = y->is_black;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->is_black = z->is_black;
  }

  if (y_original_color) {
    fix_delete(x);
  }

  delete z;
  size_--;
}

template <typename Key, typename T>
void map<Key, T>::swap(map& other) {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
}

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  for (auto it = other.begin(); it != other.end();) {
    auto current = it++;
    if (!contains(current->first)) {
      // Если ключа нет в текущем контейнере, перемещаем узел
      Node* node = current.getCurrent();
      other.transplant(node, nil_);
      node->left = nil_;
      node->right = nil_;

      // Вставляем узел в текущий контейнер
      Node* parent = nullptr;
      Node* current_node = root_;
      while (current_node != nil_) {
        parent = current_node;
        if (node->data.first < current_node->data.first) {
          current_node = current_node->left;
        } else {
          current_node = current_node->right;
        }
      }

      node->parent = parent;
      if (parent == nullptr) {
        root_ = node;
      } else if (node->data.first < parent->data.first) {
        parent->left = node;
      } else {
        parent->right = node;
      }

      node->is_black = false;
      fix_insert(node);
      size_++;
      other.size_--;
    }
  }
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) const {
  return find_node(key) != nullptr;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key& key) {
  Node* node = find_node(key);
  return node ? iterator(node, root_) : end();
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::find(const Key& key) const {
  Node* node = find_node(key);
  return node ? const_iterator(node, root_) : end();
}

// Приватные вспомогательные методы
template <typename Key, typename T>
void map<Key, T>::rotate_left(Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != nil_) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    root_ = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

template <typename Key, typename T>
void map<Key, T>::rotate_right(Node* x) {
  Node* y = x->left;
  x->left = y->right;
  if (y->right != nil_) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    root_ = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

template <typename Key, typename T>
void map<Key, T>::fix_insert(Node* z) {
  while (z != root_ && !z->parent->is_black) {
    if (z->parent == z->parent->parent->left) {
      Node* y = z->parent->parent->right;
      if (!y->is_black) {
        z->parent->is_black = true;
        y->is_black = true;
        z->parent->parent->is_black = false;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          rotate_left(z);
        }
        z->parent->is_black = true;
        z->parent->parent->is_black = false;
        rotate_right(z->parent->parent);
      }
    } else {
      Node* y = z->parent->parent->left;
      if (!y->is_black) {
        z->parent->is_black = true;
        y->is_black = true;
        z->parent->parent->is_black = false;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotate_right(z);
        }
        z->parent->is_black = true;
        z->parent->parent->is_black = false;
        rotate_left(z->parent->parent);
      }
    }
  }
  root_->is_black = true;
}

template <typename Key, typename T>
void map<Key, T>::fix_delete(Node* x) {
  while (x != root_ && x->is_black) {
    if (x == x->parent->left) {
      Node* w = x->parent->right;
      if (!w->is_black) {
        w->is_black = true;
        x->parent->is_black = false;
        rotate_left(x->parent);
        w = x->parent->right;
      }
      if (w->left->is_black && w->right->is_black) {
        w->is_black = false;
        x = x->parent;
      } else {
        if (w->right->is_black) {
          w->left->is_black = true;
          w->is_black = false;
          rotate_right(w);
          w = x->parent->right;
        }
        w->is_black = x->parent->is_black;
        x->parent->is_black = true;
        w->right->is_black = true;
        rotate_left(x->parent);
        x = root_;
      }
    } else {
      Node* w = x->parent->left;

      if (!w->is_black) {
        w->is_black = true;
        x->parent->is_black = false;
        rotate_right(x->parent);
        w = x->parent->left;
      }
      if (w->right->is_black && w->left->is_black) {
        w->is_black = false;
        x = x->parent;
      } else {
        if (w->left->is_black) {
          w->right->is_black = true;
          w->is_black = false;
          rotate_left(w);
          w = x->parent->left;
        }
        w->is_black = x->parent->is_black;
        x->parent->is_black = true;
        w->left->is_black = true;
        rotate_right(x->parent);
        x = root_;
      }
    }
  }
  x->is_black = true;
}

template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::find_node(const Key& key) const {
  Node* current = root_;
  while (current != nullptr && current != nil_) {
    if (key < current->data.first) {
      current = current->left;
    } else if (key > current->data.first) {
      current = current->right;
    } else {
      return current;
    }
  }
  return nullptr;
}

template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::copy_tree(Node* node, Node* parent) {
  if (node == nullptr) return nullptr;
  if (node == nil_) return nil_;

  Node* newNode = new Node(node->data, parent, node->is_black);

  // Копируем левое поддерево
  if (node->left != nil_) {
    newNode->left = copy_tree(node->left, newNode);
  } else {
    newNode->left = nil_;
  }

  // Копируем правое поддерево
  if (node->right != nil_) {
    newNode->right = copy_tree(node->right, newNode);
  } else {
    newNode->right = nil_;
  }

  return newNode;
}

template <typename Key, typename T>
void map<Key, T>::transplant(Node* u, Node* v) {
  if (u->parent == nullptr) {
    root_ = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::minimum(Node* node) const {
  while (node->left != nil_) {
    node = node->left;
  }
  return node;
}

};  // namespace s21

#endif  // S21_MAP_TPP