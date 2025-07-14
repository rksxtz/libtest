#include <chrono>
#include <compare>
#include <concepts>
#include <type_traits>
#include <experimental/random>

#include <ios>
#include <iostream>




namespace kw {

    template<typename _u_t> concept _move_support = requires(_u_t _a){
        requires std::is_move_constructible<_u_t>::value;
        requires std::is_move_assignable<_u_t>::value;
    };

    template<typename _u_t> concept _copy_support = requires(_u_t _a){
        requires std::is_copy_constructible<_u_t>::value;
        requires std::is_copy_assignable<_u_t>::value;
    };

    template<typename _u_t> concept _base_req_ll = requires(_u_t _dm){
        requires std::is_constructible<_u_t>::value;
        requires !std::is_pod<_u_t>::value; /* optional */
        requires std::is_default_constructible<_u_t>::value;
        { _dm } -> _move_support;
        { _dm } -> _copy_support;
    };


    template<typename _u_t> requires _base_req_ll<_u_t> class _linked_list_node {
    public:
        using key_t = _u_t;
        using node = _linked_list_node<key_t>;

    private:
        _linked_list_node(const key_t& key, node* _prev, node* next):
            key{ key }, prev{ prev }, next{ next } { }

    public:
        explicit _linked_list_node(const key_t& key):
            _linked_list_node{ key, nullptr, nullptr } { }

    public:
        key_t key; /* unique-identity */
        node* prev;
        node* next;
    };


}



int main() {
    std::ios_base::sync_with_stdio( false );

    return 0;
}