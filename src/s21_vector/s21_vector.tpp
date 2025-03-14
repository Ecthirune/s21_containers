#include "s21_vector.h"


namespace s21
{
    template<typename T>
    vector<T>::vector()
    {
        this->size_ = 0;
        this->capacity_ = 0;
        this->data_ = nullptr;
    }
}