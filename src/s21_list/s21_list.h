#include <cstddef>
#include <initializer_list>
#include <limits>
#include <memory>
namespace S21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T*;
  using iterator = Node*;
  using const_iterator = const Node*;
  using size_type = size_t;
  using allocator_type = std::allocator<T>;

 private:
  struct Node {
    T value;
    Node* next;
    Node* prev;
    Node() : value(T()), next(nullptr){};
    Node(const T& val) : value(val), next(nullptr){};
  };
  Node* head_;
  Node* tail_;
  size_t size_;

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
  const_reference front() const noexcept { return &(head_->value); }
  const_reference back() const noexcept { return &(tail_->value); }
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
    if (pos == nullptr) {
      push_back(value);
      return tail_;
    } else if (pos == head_) {
      push_front(value);
      return head_;
    }
  };

  //   void erase(iterator pos) {

  //   };

  void push_back(const_reference value) {
    Node* new_node = new Node(value);
    if (head_ == nullptr) {
      head_ = new_node;
      tail_ = new_node;
    } else {
      tail_->next = new_node;
    }
  };
};
};  // namespace S21