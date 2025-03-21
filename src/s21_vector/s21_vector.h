#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>

namespace S21 {

template <typename T>
class vector {
  /* member types */
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;
  using allocator_type = std::allocator<T>;

 private:
  T* data_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
  allocator_type allocator_;

 public:
  /* стандартный конструктор */
  vector() : data_(nullptr), size_(0), capacity_(0){};

  /* конструктор с параметром  */
  explicit vector(size_type n) : size_(n), capacity_(n) {
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
  }

  /* инициализация списка объектов */
  vector(std::initializer_list<value_type> const& items) {
    size_ = items.size();
    capacity_ = size_;
    if (size_ > 0) {
      data_ = allocator_.allocate(capacity_);
      size_type i = 0;
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

  /* конструктор копирования */
  vector(const vector& v) {
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
  }

  /* оператор перемещения */
  vector& operator=(vector&& v) noexcept {
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
  }

  /* конструктор перемещения */
  vector(vector&& v) noexcept
      : data_(v.data_),
        size_(v.size_),
        capacity_(v.capacity_),
        allocator_(std::move(v.allocator_)) {
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }

  /* возврат размера занятой памяти объектами */
  size_type size() const noexcept { return size_; }
  /* возврат размера выделенной памяти */
  size_type capacity() const noexcept { return capacity_; }
  /* максимальный размер памяти, который может быть выделен */
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }
  /* возврат итераторов на начало и конец массива */
  iterator begin() const noexcept { return data_; }
  iterator end() const noexcept { return data_ + size_; }

  const_reference front() const noexcept { return *data_; }
  const_reference back() const noexcept { return *(data_ + size_ - 1); }
  const_iterator cbegin() const noexcept { return data_; }
  const_iterator cend() const noexcept { return data_ + size_; }

  /* возврат ссылки на область памяти */
  value_type* data() const noexcept { return data_; }

  /* проверка пустой ли массив */
  bool empty() const noexcept { return size_ == 0; }

  /* срез размера массива до занимаемой области данными */
  void shrink_to_fit() {
    if (capacity_ > size_) {
      value_type* new_data = allocator_.allocate(size_);
      std::uninitialized_move(data_, data_ + size_, new_data);
      allocator_.deallocate(data_, capacity_);
      data_ = new_data;
      capacity_ = size_;
    }
  }

  /* удаление всех элементов массива */
  void clear() {
    if (data_) {
      for (size_type i = 0; i < size_; ++i) {
        data_[i].~value_type();
      }
      size_ = 0;
    }
  }

  /* удаление элемента в pos контейнера */
  void erase(iterator pos) {
    if (pos >= data_ + size_) {
      throw std::out_of_range("Out of range");
    }
    std::move(pos + 1, end(), pos);
    pop_back();
  }

  /* удаление последнего элемента контейнера */
  void pop_back() {
    if (data_) {
      data_[size_ - 1].~value_type();
      size_--;
    }
  }

  /* вставка элемента в pos контейнера */
  iterator insert(iterator pos, const_reference value) {
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
}


  /* деструктор */
  ~vector() {
    if (data_ != nullptr) {
      for (size_type i = 0; i < size_; ++i) {
        data_[i].~value_type();
      }
      allocator_.deallocate(data_, capacity_);
      size_ = 0;
      capacity_ = 0;
      data_ = nullptr;
    }
  }
  /* перемещение */
  void swap(vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(allocator_, other.allocator_);
  }
  /* доступ к элементу через at */
  reference at(size_type pos) {
    if (pos >= capacity_) {
      throw std::out_of_range("Out of range");
    }
    return data_[pos];
  }

  /* доступ к элементу через оператор */
  reference operator[](size_type pos) {
    if (pos >= capacity_) {
      throw std::out_of_range("Out of range");
    }
    return data_[pos];
  }

  const_reference operator[](size_type pos) const {
    if (pos >= capacity_) {
        throw std::out_of_range("Out of range");
    }
    return data_[pos];
}

  /* добавление элемента в конец контейнера */
  void push_back(const_reference value) {
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
  }

  /* резервирование памяти под новый размер*/
  void reserve(size_type new_capacity) {
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
  }
};
};  // namespace s21
