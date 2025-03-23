#include <cstddef>
#include <memory>

namespace S21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T*;
  using iterator = T*;
  using const_iterator = T&;
  using size_type = size_t;
  using allocator_type = std::allocator<T>;

 private:
  struct Node {
    T value;
    Node* next;
    Node(const T& val) : value(val), next(nullptr) {}
  };
  Node* head_;
  Node* tail_;
  size_t size_;

  /* удаление списка */
  void clear() {
    while (head_) {
      Node* temp = head_;
      head_ = head_->next;
      delete temp;
    }
    head_ = nullptr;
    size_ = 0;
  }

  public:
  list() : head_(nullptr), tail_(nullptr), size_(0){};

  /* конструктор с параметром */
  list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
    if (n > 0)
      for (size_type i = 0; i < n; i++) {
        Node* new_node = new Node(T());
        if constexpr (std::is_fundamental_v<value_type>) {
          new_node->value = value_type{};
        } else

        {
          std::uninitialized_default_construct_n(&new_node->value, 1);
        }
        if (!head_) {
          head_ = tail_ = new_node;
        } else {
          tail_->next = new_node;
          tail_ = new_node;
        }
        size_++;
      }
  };

  /* инциализация списка объектов */
  list(std::initializer_list<value_type> const& items)
      : head_(nullptr), tail_(nullptr), size_(0) {
    if (items.size() > 0) {
      for (const T& item : items) {
        Node* new_node = new Node(item);
        if (head_ == nullptr) {
          head_ = tail_ = new_node;
        } else {
          tail_->next = new_node;
          tail_ = new_node;
        }
        size_++;
      }
    }
  };

  /* деструктор */
  ~list() { clear(); }


  size_type size() { return size_; }
};

}  // namespace S21