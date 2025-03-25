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
  };

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
  };

  /* конструктор перемещения */
  list(list&& l) noexcept : head_(l.head_), tail_(l.tail_), size_(l.size_) {
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  };

  /* деструктор */
  ~list() { clear(); };

  /* конструктор присваивания */
  list& operator=(list&& l) noexcept {
    if (this != &l) { 
        delete head_; 
        head_ = l.head_;
        tail_ = l.tail_;
        size_ = l.size_;
        l.head_ = nullptr;
        l.tail_ = nullptr;
        l.size_ = 0;
    }
    return *this;
}

  const_reference front() const noexcept { return head_->value; };
  const_reference back() const noexcept { return tail_->value; };
  iterator begin() noexcept { return head_; };
  iterator end() noexcept { return nullptr; };
  bool empty() const noexcept { return size_ == 0; };
  size_type size() { return size_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  };

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
    Node* result = nullptr;
    /* пустой список */
    if (!head_) {
      head_ = new_node;
      tail_ = new_node;
      new_node->next = nullptr;
      new_node->prev = nullptr;
      result = new_node;
    }
    /* вставка в конец */
    else if (pos == nullptr) {
      new_node->prev = tail_;
      new_node->next = nullptr;
      tail_->next = new_node;
      tail_ = new_node;
      result = new_node;
    }
    /* вставка в начало */
    else if (pos == head_) {
      new_node->next = head_;
      head_->prev = new_node;
      head_ = new_node;
      new_node->prev = nullptr;
      result = new_node;
    }
    /* вставка в середину или отсутствие итератора pos в листе */
    else {
      Node* current = head_;
      while (current && current->next != pos) {
        current = current->next;
      }
      if (current) {
        new_node->next = pos;
        new_node->prev = current;
        current->next = new_node;
        pos->prev = new_node;
        result = new_node;
      } else {
        delete new_node;
        throw std::out_of_range("Iterator is not in the list");
      }
    }
    size_++;
    return result;
  }

  /* удаление элемента */
  void erase(iterator pos) {
    if (pos == nullptr) {
      throw std::out_of_range("Invalid iterator");
    }
    /* удаляем первый элемент */
    if (pos == head_) {
      Node* temp = head_->next;
      delete head_;
      head_ = temp;
      if (head_) {
        head_->prev = nullptr;
        if (!head_->next) {
          tail_ = head_;
        }
      } else {
        tail_ = nullptr;
      }
    } else {
      Node* previous_node = pos->prev;
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
  };

  /* добавление элемента в конец */
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

  /* удаление последнего элемента */
  void pop_back() {
    if (head_ == nullptr) {
      throw std::out_of_range("List is empty");
    }
    if (head_ == tail_) {
      delete head_;
      head_ = nullptr;

    } else {
      Node* temp = tail_->prev;
      delete tail_;
      tail_ = temp;
      tail_->next = nullptr;
    }
    size_--;
  };

  /* добавление элемента в начало */
  void push_front(const_reference value) {
    Node* new_node = new Node(value);
    if (head_ == nullptr) {
      head_ = new_node;
      tail_ = new_node;
    } else {
      Node* temp = head_;
      new_node->next = temp;
      temp->prev = new_node;
      head_ = new_node;
    }
    size_++;
  };

  /* удаление первого элемента */
  void pop_front() {
    if (head_ == nullptr) {
      throw std::out_of_range("List is empty");
    }
    if (head_ == tail_) {
      delete head_;
      head_ = nullptr;
    } else {
      Node* temp = head_->next;
      delete head_;
      head_ = temp;
      head_->prev = nullptr;
    }
  };

  /* смена данных местами */
  void swap(list& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  /* склеивание двух листов */
  void merge(list& other) noexcept {
    if (this == &other) {
      return;
    }

    if (head_ == nullptr) {
      head_ = other.head_;
      tail_ = other.tail_;
      size_ = other.size_;
    } else {
      tail_->next = other.head_;
      other.head_->prev = tail_;
      tail_ = other.tail_;
      size_ += other.size_;
    }

    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  /* перемещение данных из other на current pos */
  void splice(const_iterator pos, list& other) noexcept {
    if (this == &other) {
      return;
    }
    if (other.head_ == nullptr) {
      return;
    }
    if (pos == head_) {
      head_->prev = other.tail_;
      other.tail_->next = head_;
      head_ = other.head_;
    } else {
      if (pos == tail_) {
        tail_->next = other.head_;
        other.head_->prev = tail_;
        tail_ = other.tail_;
      } else {
        Node* current = const_cast<Node*>(pos);
        current->prev->next = other.head_;
        other.head_->prev = current->prev;
        current->prev = other.tail_;
        other.tail_->next = current;
      }
    }
    size_ += other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  };

  /* инверсия листа */
  void reverse() noexcept {
    Node* current = head_;
    while (current != nullptr) {
      std::swap(current->prev, current->next);
      current = current->prev;
    }
    std::swap(head_, tail_);
  };

  /* удаление повторяющихся элементов из листа */
  void unique() noexcept {
    if (head_ == nullptr) {
      return;
    }

    Node* current = head_;
    while (current != nullptr) {
      Node* next = current->next;
      while (next != nullptr && next->value == current->value) {
        Node* temp = next;
        next = next->next;
        if (temp == tail_) {
          tail_ = current;
        }
        if (next) {
          next->prev = current;
        }
        delete temp;
        size_--;
      }
      current = next;
    }
    if (head_ && !head_->next && size_ == 1) {
      tail_ = head_;
    } else if (size_ == 0) {
      head_ = tail_ = nullptr;
    }
  };

  void sort() {
    if (size_ <= 1) {
      return;
    }

    Node* i = head_;
    Node* j = nullptr;
    int temp;

    while (i != nullptr) {
      j = i->next;

      while (j != nullptr) {
        if (i->value > j->value) {
          temp = i->value;
          i->value = j->value;
          j->value = temp;
        }
        j = j->next;
      }
      i = i->next;
    }
  }
};

};  // namespace S21