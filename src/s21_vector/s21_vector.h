#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>

namespace s21 {

template <typename T>
class vector {
  /* member types */
 public:
  using value_type = T;

  using iterator = T*;
  using const_iterator = const T*;

  using reference = T&;
  using const_reference = const T&;

  using size_type = size_t;
  using allocator_type = std::allocator<T>;

 private:
  T* data_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
  allocator_type allocator_;

 public:
  /* стандартный конструктор */
  vector();

  /* конструктор с параметром  */
  explicit vector(size_type n);
  /* инициализация списка объектов */
  vector(std::initializer_list<value_type> const& items);

  /* конструктор копирования */
  vector(const vector& v);

  /* оператор перемещения */
  vector& operator=(vector&& v) noexcept;

  /* конструктор перемещения */
  vector(vector&& v) noexcept;

  /* возврат размера занятой памяти объектами */
  size_type size() const noexcept;

  /* возврат размера выделенной памяти */
  size_type capacity() const noexcept;

  /* максимальный размер памяти, который может быть выделен */
  size_type max_size() const noexcept;

  /* возврат итераторов на начало и конец массива */
  iterator begin() noexcept;
  iterator end() noexcept;

  reference front() noexcept;
  reference back() noexcept;
  const_reference front() const noexcept;
  const_reference back() const noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  /* возврат ссылки на область памяти */
  value_type* data() const noexcept;

  /* проверка пустой ли массив */
  bool empty() const noexcept;

  /* срез размера массива до занимаемой области данными */
  void shrink_to_fit();

  /* удаление всех элементов массива */
  void clear();

  /* удаление элемента в pos контейнера */
  void erase(iterator pos);

  /* удаление последнего элемента контейнера */
  void pop_back();

  /* вставка элемента в pos контейнера */
  iterator insert(iterator pos, const_reference value);

  /* деструктор */
  ~vector();

  /* перемещение */
  void swap(vector& other) noexcept;

  /* доступ к элементу через at */
  reference at(size_type pos);

  /* доступ к элементу через оператор */
  reference operator[](size_type pos);

  const_reference operator[](size_type pos) const;

  /* добавление элемента в конец контейнера */
  void push_back(const_reference value);

  /* резервирование памяти под новый размер*/
  void reserve(size_type new_capacity);
};
};  // namespace s21
#include "s21_vector.tpp"