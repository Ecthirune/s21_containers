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
};
} // namespace s21
