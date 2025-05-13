#ifndef S21_LIST_TPP
#define S21_LIST_TPP
namespace s21 {

template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0){};

template <typename T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
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

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items)
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

template <typename T>
list<T>::list(const list& l) : head_(nullptr), tail_(nullptr), size_(0) {
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

template <typename T>
list<T>::list(list&& l) noexcept
    : head_(l.head_), tail_(l.tail_), size_(l.size_) {
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
};

template <typename T>
typename list<T>::list& list<T>::list::operator=(list&& l) noexcept {
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

template <typename T>
typename list<T>::const_reference list<T>::front() const noexcept {
  return head_->value;
};

template <typename T>
typename list<T>::const_reference list<T>::back() const noexcept {
  return tail_->value;
};

template <typename T>
typename list<T>::iterator list<T>::begin() noexcept {
  return head_;
};

template <typename T>
typename list<T>::iterator list<T>::end() noexcept {
  return nullptr;
};

template <typename T>
bool list<T>::empty() const noexcept {
  return size_ == 0;
};

template <typename T>
typename list<T>::size_type list<T>::size() {
  return size_;
};

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max();
};

template <typename T>
void list<T>::clear() {
  while (head_) {
    Node* temp = head_;
    head_ = head_->next;
    delete temp;
  }
  head_ = nullptr;
  size_ = 0;
};

template <typename T>
typename list<T>::iterator list<T>::insert(
    typename list<T>::iterator pos, typename list<T>::const_reference value) {
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
  else if (pos == end()) {
    new_node->prev = tail_;
    new_node->next = nullptr;
    tail_->next = new_node;
    tail_ = new_node;
    result = new_node;
  }
  /* вставка в начало */
  else if (pos == begin()) {
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

template <typename T>
void list<T>::erase(typename list<T>::iterator pos) {
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

template <typename T>
void list<T>::push_back(typename list<T>::const_reference value) noexcept {
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

template <typename T>
void list<T>::pop_back() {
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

template <typename T>
void list<T>::push_front(typename list<T>::const_reference value) {
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

template <typename T>
void list<T>::pop_front() {
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
  size_--;
};

template <typename T>
void list<T>::swap(typename list<T>::list& other) noexcept {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
};

template <typename T>
void list<T>::merge(typename list<T>::list& other) noexcept {
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
};

template <typename T>
void list<T>::splice(typename list<T>::const_iterator pos,
                     typename list<T>::list& other) noexcept {
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

template <typename T>
void list<T>::reverse() noexcept {
  Node* current = head_;
  while (current != nullptr) {
    std::swap(current->prev, current->next);
    current = current->prev;
  }
  std::swap(head_, tail_);
};

template <typename T>
void list<T>::unique() noexcept {
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

template <typename T>
void list<T>::sort() {
  if (size_ <= 1) {
    return;
  }

  /* Разделяем список на две части */
  Node* slow = head_;
  Node* fast = head_->next;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }

  /* Создаем второй список */
  list second;
  second.head_ = slow->next;
  second.tail_ = tail_;
  second.size_ = size_ / 2;

  /* Обрезаем первый список */
  slow->next = nullptr;
  tail_ = slow;
  size_ = (size_ + 1) / 2;

  /* Рекурсивно сортируем обе части */
  sort();
  second.sort();

  /* Сливаем отсортированные списки */
  Node* current = nullptr;
  Node* first = head_;
  Node* second_head = second.head_;

  /* Выбираем новый head */
  if (first->value <= second_head->value) {
    head_ = first;
    current = first;
    first = first->next;
  } else {
    head_ = second_head;
    current = second_head;
    second_head = second_head->next;
  }

  /* Сливаем оставшиеся элементы */
  while (first != nullptr && second_head != nullptr) {
    if (first->value <= second_head->value) {
      current->next = first;
      first->prev = current;
      current = first;
      first = first->next;
    } else {
      current->next = second_head;
      second_head->prev = current;
      current = second_head;
      second_head = second_head->next;
    }
  }

  /* Добавляем оставшиеся элементы */
  if (first != nullptr) {
    current->next = first;
    first->prev = current;
    tail_ = first;
    while (tail_->next != nullptr) {
      tail_ = tail_->next;
    }
  } else if (second_head != nullptr) {
    current->next = second_head;
    second_head->prev = current;
    tail_ = second_head;
    while (tail_->next != nullptr) {
      tail_ = tail_->next;
    }
  }

  /* Обновляем размер */
  size_ += second.size_;

  /* Очищаем второй список */
  second.head_ = nullptr;
  second.tail_ = nullptr;
  second.size_ = 0;
};

template <typename T>
bool list<T>::list::operator==(
    const typename list<T>::list& other) const noexcept {
  if (size_ != other.size_) return false;
  Node* current1 = head_;
  Node* current2 = other.head_;
  while (current1 != nullptr) {
    if (current1->value != current2->value) return false;
    current1 = current1->next;
    current2 = current2->next;
  }
  return true;
};

template <typename T>
bool list<T>::list::operator!=(
    const typename list<T>::list& other) const noexcept {
  return !(*this == other);
};

template <typename T>
bool list<T>::list::operator<(
    const typename list<T>::list& other) const noexcept {
  Node* current1 = head_;
  Node* current2 = other.head_;
  while (current1 != nullptr && current2 != nullptr) {
    if (current1->value < current2->value) return true;
    if (current1->value > current2->value) return false;
    current1 = current1->next;
    current2 = current2->next;
  }
  return size_ < other.size_;
};

template <typename T>
bool list<T>::list::operator>(
    const typename list<T>::list& other) const noexcept {
  return other < *this;
};

template <typename T>
bool list<T>::list::operator<=(
    const typename list<T>::list& other) const noexcept {
  return !(other < *this);
};

template <typename T>
typename list<T>::iterator& list<T>::list::operator++() noexcept {
  if (head_) head_ = head_->next;
  return *this;
};

template <typename T>
typename list<T>::iterator list<T>::list::operator++(int) noexcept {
  iterator temp = head_;
  if (head_) head_ = head_->next;
  return temp;
};

template <typename T>
typename list<T>::iterator& list<T>::list::operator--() noexcept {
  if (head_) head_ = head_->prev;
  return *this;
};

template <typename T>
typename list<T>::iterator list<T>::list::operator--(int) noexcept {
  iterator temp = head_;
  if (head_) head_ = head_->prev;
  return temp;
};

template <typename T>
typename list<T>::list list<T>::list::operator+(
    const typename list<T>::list& other) const noexcept {
  list result(*this);
  Node* current = other.head_;
  while (current != nullptr) {
    result.push_back(current->value);
    current = current->next;
  }
  return result;
};

template <typename T>
typename list<T>::list& list<T>::list::operator+=(
    const typename list<T>::list& other) noexcept {
  Node* current = other.head_;
  while (current != nullptr) {
    push_back(current->value);
    current = current->next;
  }
  return *this;
};

template <typename T>
typename list<T>::list list<T>::list::operator-(
    const typename list<T>::list& other) const noexcept {
  list result(*this);
  Node* current = other.head_;
  while (current != nullptr) {
    bool removed = false;
    Node* temp = result.head_;
    Node* prev = nullptr;
    while (temp != nullptr && !removed) {
      if (temp->value == current->value) {
        Node* to_delete = temp;
        if (temp == result.head_) {
          result.head_ = temp->next;
        }
        if (temp == result.tail_) {
          result.tail_ = temp->prev;
        }
        if (temp->prev) {
          temp->prev->next = temp->next;
        }
        if (temp->next) {
          temp->next->prev = temp->prev;
        }
        temp = temp->next;
        delete to_delete;
        result.size_--;
        removed = true;
      } else {
        temp = temp->next;
      }
    }
    current = current->next;
  }
  return result;
};

template <typename T>
typename list<T>::list& list<T>::list::operator-=(
    const typename list<T>::list& other) noexcept {
  Node* current = other.head_;
  while (current != nullptr) {
    Node* temp = head_;
    while (temp != nullptr) {
      if (temp->value == current->value) {
        Node* to_delete = temp;
        if (temp == head_) head_ = temp->next;
        if (temp == tail_) tail_ = temp->prev;
        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
        temp = temp->next;
        delete to_delete;
        size_--;
        break;
      }
      temp = temp->next;
    }
    current = current->next;
  }
  return *this;
}

}  // namespace s21
#endif  // S21_LIST_H