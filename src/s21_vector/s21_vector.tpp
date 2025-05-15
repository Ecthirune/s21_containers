#ifndef S21_VECTOR_TPP_
#define S21_VECTOR_TPP_
#include <initializer_list>

namespace s21 {

template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0){};

template <typename T>
vector<T>::vector(size_type n) : size_(n), capacity_(n) {
  if (size_ > 0) {
    data_ = allocator_.allocate(capacity_);
    // если T стандартный тип данных
    if constexpr (std::is_fundamental_v<value_type>) {
      // инициализируем память
      std::uninitialized_fill_n(data_, size_, value_type{});
    } else {
      // инициализируем память конструкторами T
      std::uninitialized_default_construct_n(data_, size_);
    }
  }
};

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items) {
  size_ = items.size();
  capacity_ = size_;
  if (size_ > 0) {
    data_ = allocator_.allocate(capacity_);
    try {
      std::uninitialized_copy(items.begin(), items.end(), data_);
    } catch (...) {
      allocator_.deallocate(data_, capacity_);
      throw;
    }
  } else {
    data_ = nullptr;
  }
}

template <typename T>
vector<T>::vector(const vector& v) {
  size_ = v.size();
  capacity_ = v.capacity();
  if (size_ > 0) {
    data_ = allocator_.allocate(capacity_);
    try {
      std::uninitialized_copy(v.begin(), v.end(), data_);
    } catch (...) {
      allocator_.deallocate(data_, capacity_);
      throw;
    }
  }
};

template <typename T>
typename vector<T>::vector& vector<T>::operator=(vector&& v) noexcept {
  if (this != &v) {
    if (data_) {
      for (size_type i = 0; i < size_; ++i) {
        data_[i].~value_type();
      }
      allocator_.deallocate(data_, capacity_);
    }
    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
};

template <typename T>
vector<T>::vector(vector&& v) noexcept
    : data_(v.data_),
      size_(v.size_),
      capacity_(v.capacity_),
      allocator_(std::move(v.allocator_)) {
  v.data_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
};

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
};

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max();
};

template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
  return data_;
};

template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
  return data_ + size_;
};

template <typename T>
typename vector<T>::reference vector<T>::front() noexcept {
  return *data_;
};

template <typename T>
typename vector<T>::reference vector<T>::back() noexcept {
  return *(data_ + size_ - 1);
};

template <typename T>
typename vector<T>::const_reference vector<T>::front() const noexcept {
  return *data_;
};

template <typename T>
typename vector<T>::const_reference vector<T>::back() const noexcept {
  return *(data_ + size_ - 1);
};

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const noexcept {
  return data_;
};

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const noexcept {
  return data_ + size_;
};

template <typename T>
typename vector<T>::value_type* vector<T>::data() const noexcept {
  return data_;
};

template <typename T>
bool vector<T>::empty() const noexcept {
  return size_ == 0;
};

template <typename T>
void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    value_type* new_data = allocator_.allocate(size_);
    std::uninitialized_move(data_, data_ + size_, new_data);
    allocator_.deallocate(data_, capacity_);
    data_ = new_data;
    capacity_ = size_;
  }
};

template <typename T>
void vector<T>::clear() {
  if (data_) {
    for (size_type i = 0; i < size_; ++i) {
      data_[i].~value_type();
    }
    size_ = 0;
  }
};

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos >= data_ + size_) {
    throw std::out_of_range("Out of range");
  }
  std::move(pos + 1, end(), pos);
  pop_back();
};

template <typename T>
void vector<T>::pop_back() {
  if (data_) {
    data_[size_ - 1].~value_type();
    size_--;
  }
};

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Out of range");
  }

  ptrdiff_t offset = pos - begin();

  if (size_ >= capacity_) {
    size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    value_type* new_data = allocator_.allocate(new_capacity);
    std::uninitialized_copy(data_, pos, new_data);
    new (new_data + offset) value_type(value);
    std::uninitialized_copy(pos, end(), new_data + offset + 1);
    allocator_.deallocate(data_, capacity_);
    data_ = new_data;
    capacity_ = new_capacity;
  } else {
    std::move(pos, end(), pos + 1);
    new (pos) value_type(value);
  }

  size_++;
  return begin() + offset;
};

template <typename T>
vector<T>::~vector() {
  if (data_ != nullptr) {
    for (size_type i = 0; i < size_; ++i) {
      data_[i].~value_type();
    }
    allocator_.deallocate(data_, capacity_);
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
  }
};

template <typename T>
void vector<T>::swap(vector& other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(allocator_, other.allocator_);
};

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= capacity_) {
    throw std::out_of_range("Out of range");
  }
  return data_[pos];
};

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= capacity_) {
    throw std::out_of_range("Out of range");
  }
  return data_[pos];
};

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  if (pos >= capacity_) {
    throw std::out_of_range("Out of range");
  }
  return data_[pos];
};

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    value_type* new_data = allocator_.allocate(new_capacity);
    for (size_type i = 0; i < size_; ++i) {
      new (new_data + i) value_type(std::move(data_[i]));
      data_[i].~value_type();
    }
    new (new_data + size_) value_type(value);
    allocator_.deallocate(data_, capacity_);
    capacity_ = new_capacity;
    data_ = new_data;
  } else {
    new (data_ + size_) value_type(value);
  }
  size_++;
};

template <typename T>
void vector<T>::reserve(size_type new_capacity) {
  if (new_capacity > capacity_) {
    value_type* new_data = allocator_.allocate(new_capacity);
    for (size_type i = 0; i < size_; ++i) {
      new (new_data + i) value_type(std::move(data_[i]));
      data_[i].~value_type();
    }
    allocator_.deallocate(data_, capacity_);
    capacity_ = new_capacity;
    data_ = new_data;
  }
};

};  // namespace s21

#endif  // S21_VECTOR_TPP_