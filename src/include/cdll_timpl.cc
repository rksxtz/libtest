#include <memory>
#include <experimental/random>

#include <string>
#include <vector>

#include <fstream>
#include <ostream>
#include <iostream>



namespace kw {

    template<typename _u_t> class _linked_list_node {
    public:
        using key_t = _u_t;
        using node = _linked_list_node<key_t>;

        explicit _linked_list_node(node* _prev = nullptr, node* _next = nullptr, key_t _key = {}):
            prev{ _prev }, next{ _next }, key{ _key } { }

        explicit _linked_list_node(const key_t key):
            _linked_list_node{ nullptr, nullptr, key } { }

        _linked_list_node(const _linked_list_node<key_t>& _cp_node):
            _linked_list_node{ _cp_node.prev, _cp_node.next, _cp_node.key } { }

        _linked_list_node(_linked_list_node<key_t>&& _mv_node) noexcept:
            _linked_list_node{ _mv_node.prev, _mv_node.next, _mv_node.key } {
            _mv_node.prev = _mv_node.next = nullptr, _mv_node.key = key_t{};
        }

    private:
        node* prev;
        node* next;
        key_t key;
    };

    template<typename _u_t> class linkedlist {
    public:
        using key_t = _u_t;
        using node = kw::_linked_list_node<key_t>;
        using linked_list_t = linkedlist<key_t>; /* Miscellaneous */

        explicit linkedlist(node* head = nullptr):
            _m_sentinel{ new (std::nothrow) node{ } }, nil{ nullptr }, _m_node_pool{ } {
            this->nil = this->_m_sentinel.get();
            this->nil->next = this->nil->prev = this->nil;
            if (head) {
                head->prev = this->nil, this->nil->next = head;
                this->_m_node_pool.emplace_back( head );
                while (head->next)
                    head = head->next, this->_m_node_pool.emplace_back( head );
                head->next = this->nil, this->nil->prev = head;
            }
        }

        void insert(node* _node) {
            if (_node) {
                _node->next = this->nil->next, _node->prev = this->nil;
                this->nil->next->prev = _node;
                this->nil->next = _node;
                this->_m_node_pool.emplace_back( _node );
            }
        }

        void insert(const key_t key) {
            insert( new (std::nothrow) node{ nullptr, nullptr, key } );
        }

    private:
        std::unique_ptr<node> _m_sentinel; /* Holds the sentinel, just for the purpose of RAII + Memory Safety */
        node* nil;
        std::vector<std::unique_ptr<node>> _m_node_pool;
    };

}



int main() {
    return 0;
}