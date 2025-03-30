#include <cstddef>
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>

namespace s21 {
template <typename Key, typename T> class map {
public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  // using iterator =
  // using const_iterator =
  using size_type = size_t;

private:
  struct Node {
    value_type data;
    Node *parent;
    Node *links[2];
    bool is_red;
    Node(const value_type &val, bool is_red = true)
        : data(val), parent(nullptr), links{nullptr, nullptr}, is_red(is_red) {}
  };

  struct Sentinel {
    // fake node
  };
  Node *root_;
  size_type size_;

  void delete_node(Node *node) {
    if (node) {
      delete_node(node->links[0]);
      delete_node(node->links[1]);
      delete node;
    }
  }

  Node* copy_node(Node* node, Node* parent) {
    if (node == nullptr) {
      return nullptr;
    }
    Node* new_node = new Node(node->data, node->is_red);
    new_node->parent = parent;
    new_node->links[0] = copy_node(node->links[0], new_node);
    new_node->links[1] = copy_node(node->links[1], new_node);
    return new_node;
  }

  

  void balance_tree(Node *current) {
    if (current == nullptr) {
      return;
    }

    bool balancing_complete = false;
    
    while (!balancing_complete && current->parent != nullptr) {
      Node *parent = current->parent;
      Node *grandparent = parent->parent;
      
      if (parent->is_red) {
        if (grandparent == nullptr) {
          parent->is_red = false;
          balancing_complete = true;
        } else {
          Node *uncle = nullptr;
          if (parent == grandparent->links[0]) {
            uncle = grandparent->links[1];
          } else {
            uncle = grandparent->links[0];
          }
          
          if (uncle != nullptr && uncle->is_red) {
            parent->is_red = false;
            uncle->is_red = false;
            grandparent->is_red = true;
            current = grandparent;
          } else {
            bool is_left_case = current == parent->links[0];
            bool parent_is_left = parent == grandparent->links[0];
            
            if (!is_left_case && parent_is_left) {
              rotate_left(parent);
              current = parent;
              parent = current->parent;
            } else if (is_left_case && !parent_is_left) {
              rotate_right(parent);
              current = parent;
              parent = current->parent;
            }
            
            parent->is_red = false;
            grandparent->is_red = true;
            
            if (current == parent->links[0]) {
              rotate_right(grandparent);
            } else {
              rotate_left(grandparent);
            }
            
            balancing_complete = true;
          }
        }
      } else {
        balancing_complete = true;
      }
    }
    
    if (root_ != nullptr) {
      root_->is_red = false;
    }
  }

  void rotate_left(Node *node) {
    if (node == nullptr || node->links[1] == nullptr) {
      return;
    }

    Node *right = node->links[1];
    node->links[1] = right->links[0];
    
    if (right->links[0] != nullptr) {
      right->links[0]->parent = node;
    }
    
    right->parent = node->parent;
    
    if (node->parent == nullptr) {
      root_ = right;
    } else if (node == node->parent->links[0]) {
      node->parent->links[0] = right;
    } else {
      node->parent->links[1] = right;
    }
    
    right->links[0] = node;
    node->parent = right;
  }

  void rotate_right(Node *node) {
    if (node == nullptr || node->links[0] == nullptr) {
      return;
    }

    Node *left = node->links[0];
    node->links[0] = left->links[1];
    
    if (left->links[1] != nullptr) {
      left->links[1]->parent = node;
    }
    
    left->parent = node->parent;
    
    if (node->parent == nullptr) {
      root_ = left;
    } else if (node == node->parent->links[1]) {
      node->parent->links[1] = left;
    } else {
      node->parent->links[0] = left;
    }
    
    left->links[1] = node;
    node->parent = left;
  }

public:
  /* стандартный конструктор */
  map() : root_(nullptr), size_(0){};

  /* конструктор на основе списка */
  map(std::initializer_list<value_type> const &items)
      : root_(nullptr), size_(0) {
    for (auto item : items) {
      insert(item);
    }
  };

  /* конструктор копирования */
  map(const map &m) : root_(nullptr), size_(0) {
    if (m.root_ != nullptr) {
      root_ = copy_node(m.root_, nullptr);
      size_ = m.size_;
    }
  };

  /* конструктор перемещения */
  map(map &&m) : root_(m.root_), size_(m.size_) {
    m.root_ = nullptr;
    m.size_ = 0;
  }

  /* оператор присваивания */
  map &operator=(const map &mm) {
    if (this != &mm) {
      delete_node(root_);
      root_ = nullptr;
      size_ = 0;
      if (mm.root_) {
        root_ = copy_node(mm.root_, nullptr);
        size_ = mm.size_;
      }
    }
    return *this;
  };

public:
  /* деструктор */
  ~map() { delete_node(root_); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }

  std::pair<Node *, bool> insert(const value_type &val) {
    Node *current = root_;
    Node *parent = nullptr;
    bool value_not_exists = true;
    bool direction = false; /* false - левый потомок, true - правый потомок*/

    while (current != nullptr && value_not_exists) {
      parent = current;
      direction = val.first > current->data.first;
      if (val.first == current->data.first) {
        value_not_exists = false;
      } else {
        current = current->links[direction];
      }
    }

    Node *new_node = nullptr;
    if (value_not_exists) {
      new_node = new Node(val, true);
      new_node->parent = parent;
      size_++;

      if (parent == nullptr) {
        root_ = new_node;
      } else {
        parent->links[direction] = new_node;
      }
      balance_tree(new_node);
    } else {
      new_node = current;
    }
    return {new_node, value_not_exists};
  }
};
} // namespace s21
