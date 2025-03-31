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
  using size_type = size_t;

private:


  struct Node {
    value_type data;
    Node *parent;
    Node *links[2];
    bool is_red;
    Node() : data{Key{}, T{}}, parent(nullptr), links{nullptr, nullptr}, is_red(false) {}
    Node(const value_type &val, bool is_red = true)
        : data(val), parent(nullptr), links{nullptr, nullptr}, is_red(is_red) {
        links[0] = &sentinel_;
        links[1] = &sentinel_;
    }
  };

  inline static Node sentinel_{};


  Node *root_;
  size_type size_;

  void delete_node(Node *node) {
    if (node && node != &sentinel_) {
      delete_node(node->links[0]);
      delete_node(node->links[1]);
      delete node;
    }
  }

  Node* copy_node(Node* node, Node* parent) {
    if (node == nullptr || node == &sentinel_) {
      return &sentinel_;
    }
    Node* new_node = new Node(node->data, node->is_red);
    new_node->parent = parent;
    new_node->links[0] = copy_node(node->links[0], new_node);
    new_node->links[1] = copy_node(node->links[1], new_node);
    return new_node;
  }

  void balance_tree(Node *current) {
    if (current == nullptr || current == &sentinel_) {
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
          
          if (uncle != &sentinel_ && uncle->is_red) {
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
    if (node == nullptr || node->links[1] == &sentinel_) {
      return;
    }

    Node *right = node->links[1];
    node->links[1] = right->links[0];
    
    if (right->links[0] != &sentinel_) {
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
    if (node == nullptr || node->links[0] == &sentinel_) {
      return;
    }

    Node *left = node->links[0];
    node->links[0] = left->links[1];
    
    if (left->links[1] != &sentinel_) {
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
  class MapIterator {
  private:
      Node* current_;
      Node* root_;
      bool is_end_;

      Node* find_min(Node* node) {
          Node* result = &sentinel_;
          if (node != nullptr && node != &sentinel_) {
              result = node;
              while (result->links[0] != &sentinel_) {
                  result = result->links[0];
              }
          }
          return result;
      }

      Node* find_max(Node* node) {
          Node* result = &sentinel_;
          if (node != nullptr && node != &sentinel_) {
              result = node;
              while (result->links[1] != &sentinel_) {
                  result = result->links[1];
              }
          }
          return result;
      }

      Node* find_next(Node* node) {
          Node* result = &sentinel_;
          
          if (node != nullptr && node != &sentinel_) {
              if (node->links[1] != &sentinel_) {
                  result = find_min(node->links[1]);
              } else {
                  Node* parent = node->parent;
                  while (parent != nullptr && node == parent->links[1]) {
                      node = parent;
                      parent = parent->parent;
                  }
                  result = parent != nullptr ? parent : &sentinel_;
              }
          }
          
          return result;
      }

      Node* find_prev(Node* node) {
          Node* result = &sentinel_;
          
          if (node == nullptr || node == &sentinel_) {
              result = find_max(root_);
          } else if (node->links[0] != &sentinel_) {
              result = find_max(node->links[0]);
          } else {
              Node* parent = node->parent;
              while (parent != nullptr && node == parent->links[0]) {
                  node = parent;
                  parent = parent->parent;
              }
              result = parent != nullptr ? parent : &sentinel_;
          }
          
          return result;
      }

  public:
      struct iterator_category {
          static constexpr bool is_bidirectional = true;
      };
      using value_type = std::pair<const Key, T>;
      using difference_type = long long;
      using pointer = value_type*;
      using reference = value_type&;

      MapIterator() : current_(&sentinel_), root_(nullptr), is_end_(true) {}
      
      MapIterator(Node* node, Node* root) 
          : current_(node), root_(root), is_end_(node == &sentinel_) {}

      MapIterator(const MapIterator& other) 
          : current_(other.current_), root_(other.root_), is_end_(other.is_end_) {}

      MapIterator& operator=(const MapIterator& other) {
          if (this != &other) {
              current_ = other.current_;
              root_ = other.root_;
              is_end_ = other.is_end_;
          }
          return *this;
      }

      reference operator*() {
          reference result = current_->data;
          if (current_ == &sentinel_) {
              throw std::out_of_range("Выход за границы контейнера");
          }
          return result;
      }

      pointer operator->() {
          pointer result = &(current_->data);
          if (current_ == &sentinel_) {
              throw std::out_of_range("Выход за границы контейнера");
          }
          return result;
      }

      MapIterator& operator++() {
          if (!is_end_) {
              current_ = find_next(current_);
              is_end_ = (current_ == &sentinel_);
          }
          return *this;
      }

      MapIterator operator++(int) {
          MapIterator temp(*this);
          ++(*this);
          return temp;
      }

      MapIterator& operator--() {
          if (is_end_) {
              current_ = find_max(root_);
              is_end_ = false;
          } else {
              current_ = find_prev(current_);
              is_end_ = (current_ == &sentinel_);
          }
          return *this;
      }

      MapIterator operator--(int) {
          MapIterator temp(*this);
          --(*this);
          return temp;
      }

      bool operator==(const MapIterator& other) const {
          bool result = current_ == other.current_;
          return result;
      }

      bool operator!=(const MapIterator& other) const {
          bool result = !(*this == other);
          return result;
      }
  };

  using iterator = MapIterator;
  using const_iterator = const MapIterator;

  iterator begin() { 
    if (root_ == nullptr) {
      return end();
    }
    Node* current = root_;
    while (current->links[0] != &sentinel_) {
      current = current->links[0];
    }
    return MapIterator(current, root_);
  }

  const_iterator begin() const { 
    if (root_ == nullptr) {
      return end();
    }
    Node* current = root_;
    while (current->links[0] != &sentinel_) {
      current = current->links[0];
    }
    return MapIterator(current, root_);
  }

  const_iterator cbegin() const { 
    return begin();
  }

  iterator end() { return MapIterator(&sentinel_, root_); }
  const_iterator end() const { return MapIterator(&sentinel_, root_); }  
  const_iterator cend() const { return end(); }

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

  /* деструктор */
  ~map() { delete_node(root_); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    bool inserted = false;
    iterator result = MapIterator(nullptr, root_);
    
    auto it = find(key);
    if (it != end()) {
      it->second = obj;
      result = it;
    } else {
      value_type val = {key, obj};
      auto [new_it, success] = insert(val);
      result = new_it;
      inserted = success;
    }
    
    return {result, inserted};
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    value_type val = {key, obj};
    return insert(val);
  }

  std::pair<iterator, bool> insert(const value_type &val) {
    Node *current = root_;
    Node *parent = nullptr;
    bool value_not_exists = true;
    bool direction = false;

    while (current != nullptr && current != &sentinel_ && value_not_exists) {
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
    return {MapIterator(new_node, root_), value_not_exists};
  }

  iterator find(const Key& key) {
    Node *current = root_;
    while (current != nullptr && current != &sentinel_) {
      if (key < current->data.first) {
        current = current->links[0];
      } else if (key > current->data.first) {
        current = current->links[1];
      } else {
        return MapIterator(current, root_);
      }
    }
    return end();
  }

  const_iterator find(const Key& key) const {
    Node *current = root_;
    while (current != nullptr && current != &sentinel_) {
      if (key < current->data.first) {
        current = current->links[0];
      } else if (key > current->data.first) {
        current = current->links[1];
      } else {
        return MapIterator(current, root_);
      }
    }
    return end();
  }
};
} // namespace s21
