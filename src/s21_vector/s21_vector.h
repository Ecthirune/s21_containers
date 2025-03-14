#include 

namespace s21
{
    template <typename T>
    class vector
    {
        private:
        T* data_;
        size_t size_;
        size_t capacity_;
    public:

        /* member types */
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = size_t;
        

        vector();
        vector(size_type n);
        vector(std::initializer_list<value_type> const& items);
        vector(const vector& v);
        vector(vector&& v);
        ~vector();
        operator=(vector &&v);
        

    };
};


int main()
{

}