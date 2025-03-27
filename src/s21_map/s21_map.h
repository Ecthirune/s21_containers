#include <cstddef>
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>



namespace s21
{
    template <typename Key, typename T>
    class map
    {
        public:
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        // using iterator = 
        // using const_iterator = 
        using size_type = size_t;

        private:
        struct Node
        {
            mapped_type data;
            Node* parent;
            Node* left;
            Node* right;
            Bool isRed;
            Node(const value_type& val, Bool isRed = true) 
            : data(val), left(nullptr), right(nullptr), parent(nullptr),
        };
        struct Sentinel
        {
            // fake node
        }
        Node* root;
        size_type size_;

        map(): root(nullptr), size_(0) {}
        map(std::initializer_list<value_type> const &items)
        {
            
        }
        
        
    };
}


