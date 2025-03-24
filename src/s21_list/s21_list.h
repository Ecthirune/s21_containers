#include <cstddef>
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>

namespace S21 {

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
  list() : head_(nullptr), tail_(nullptr), size_(0){};

  /* конструктор с параметром */
  list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
    if (n > 0) {
      for (size_type i = 0; i < n; i++) {
        Node* new_node = new Node();
        new_node->next = nullptr;
        new_node->prev = nullptr;
        if (head_ == nullptr) {
          head_ = new_node;
          tail_ = new_node;
        } else {
          tail_->next = new_node;
          new_node->prev = tail_;
          tail_ = new_node;
        }
        size_++;
      }
    }
  }

  /* инциализация списка объектов */
  list(std::initializer_list<value_type> const& items)
      : head_(nullptr), tail_(nullptr), size_(0) {
    if (items.size() > 0) {
      for (const T& item : items) {
        Node* new_node = new Node(item);
        if (head_ == nullptr) {
          head_ = new_node;
          tail_ = new_node;
        } else {
          tail_->next = new_node;
          new_node->prev = tail_;
          tail_ = new_node;
        }
        size_++;
      }
    }
  };

  /* конструктор копирования */
  list(const list& l) : head_(nullptr), tail_(nullptr), size_(0) {
    Node* current_node = l.head_;
    Node* prev_node = nullptr;

    while (current_node != nullptr) {
      Node* new_node = new Node(current_node->value);
      new_node->next = nullptr;
      new_node->prev = nullptr;

      if (head_ == nullptr) {
        head_ = new_node;
        tail_ = new_node;
      } else {
        prev_node->next = new_node;
        new_node->prev = prev_node;
        tail_ = new_node;
      }

      prev_node = new_node;
      current_node = current_node->next;
      size_++;
    }
  }

  /* конструктор перемещения */
  list(list&& l) noexcept : head_(l.head_), tail_(l.tail_), size_(l.size_) {
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }

  /* деструктор */
  ~list() { clear(); }

  /* конструктор присваивания */
  list& operator=(list&& l) noexcept {
    if (this != l) {
      while (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
      }
      tail_ = nullptr;
      size_ = 0;

      head_ = l.head_;
      tail_ = l.tail_;
      size_ = l.size_;

      l.head_ = nullptr;
      l.tail_ = nullptr;
      l.size_ = 0;
    }
    return *this;
  }

  const_reference front() const noexcept { return head_->value; }
  const_reference back() const noexcept { return tail_->value; }
  iterator begin() noexcept { return head_; }
  iterator end() noexcept { return nullptr; }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() { return size_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }

  /* удаление списка */
  void clear() {
    while (head_) {
      Node* temp = head_;
      head_ = head_->next;
      delete temp;
    }
    head_ = nullptr;
    size_ = 0;
  };

  iterator insert(iterator pos, const_reference value) {
    Node* new_node = new Node(value);
    if (pos == nullptr || head_ == pos) {
      new_node->next = head_;
      if (head_) {
        head_->prev = new_node;
      }
      head_ = new_node;
    } else {
      Node* current = head_;
      while (current && current->next != pos) {
        current = current->next;
      }
      if (current) {
        new_node->next = pos;
        new_node->prev = current;
        current->next = new_node;
        pos->prev = new_node;
      } else {
        delete new_node;
        throw std::out_of_range("Iterator is not in the list");
      }
    }
    return new_node;
  };

  void erase(iterator pos) {
    if (pos == nullptr) {
      throw std::out_of_range("Invalid iterator");
    }

    if (pos == head_) {
      Node* temp = head_->next;
      delete head_;
      head_ = temp;
      if (head_) {
        head_->prev = nullptr;
      } else {
        tail_ = nullptr;
      }
    } else {
      Node* previous_node = pos->next;
      Node* next_node = pos->next;
      delete pos;
      previous_node->next = next_node;
      if (next_node) {
        next_node->prev = previous_node;
      } else {
        tail_ = previous_node;
      }
    }
    size_--;
  }

  void push_back(const_reference value) {
    Node* new_node = new Node(value);
    if (head_ == nullptr) {
      head_ = new_node;
      tail_ = new_node;
    } else {
      tail_->next = new_node;
      new_node->prev = tail_;
      tail_ = new_node;
    }
    size_++;
  };

  void push_front(const_reference value) {
    Node* new_node = new Node(value);
    if (head_ == nullptr) {
      head_ = new_node;
      tail_ = new_node;
    } else {
      new_node->next = head_;
      head_->prev = new_node;
      head_ = new_node;
    }
    size_++;
  };
};
};  // namespace S21