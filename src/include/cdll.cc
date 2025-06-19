#include <memory>
#include <limtis>
#include <experimental/random>

#include <string>
#include <vector>

#include <ostream>
#include <iostream>


#define __random_range__(low, high) std::experimental::randint(low, high)
#define __random__() __random_range__( -int{ std::numeric_limits<unsigned char>::max() }, -int{ std::numeric_limits<unsigned char>::max() })


namespace kw{

    template<typename _u_t> class _linked_list_node{
        public:
            using key_t = _u_t;
            using node = _linked_list_node<key_t>;
        
        explicit _linked_list_node( key_t key = key_t{} ):
            key{ }, next{ nullptr }, prev{ nullptr } { }
        
        explicit _linked_list_node( const _linked_list_node& _cp_node ):
            _linked_list_node{ _cp_node.key, _cp_node.next, _cp_node.prev } { }
        
        key_t key;
        node* next;
        node* prev;
    };

    template<typename _u_t> class linkedlist{
        public:
            using key_t = _u_t;
            using node = _linked_list_node<key_t>;

            explicit linkedlist( node* _head_ = nullptr):
                _m_sentinel{ std::unique_ptr<node>{ new (std::nothrow) node{ key_t{}, nullptr, nullptr } } }, nil{ nullptr },
                head{ _head_ }, pool{ } {
                    this->nil = this->_m_sentinel.get();
                    this->nil->next = this->nil->prev = this->nil;
                    if(!this->head){
                        this->head = this->nil;
                    }
                }

            /*
                Each of the following function is just minimal, and thus does not provide any checking for nullptr
                We do not need a destructor, since its all handled by std::unique_ptr's
            */

            void insert(node* _node){
                _node->next = this->nil->next;
                this->nil->next->prev = _node;
                this->nil->next = _node, _node->prev = this->nil;
                this->head = _node;
                this->pool.emplace_back( std::unique_ptr<node>{ _node } );
            }

            void insert(key_t key){
                insert( new (std::nothrow) node{ key, nullptr, nullptr } );
            }

            void remove(node* node){
                node->next->prev = node->prev;
                node->prev->next = node->next;
                if(this->head == node)
                    this->head = node->next; /* or this->head = this->nil->next (as this->nil will be updated by now) */
            }

            void remove(key_t key){
                remove( search( key ) );
            }

            node* search(key_t key){
                node* _cnode = this->nil->next;
                while(_cnode != this->nil && (_cnode->key != key))
                    _cnode = _cnode->next;
                return _cnode == this->nil ? nullptr : _cnode;
            }

        private:
            std::unique_ptr<node> _m_sentinel;
            node* nil;
            node* head;
            std::vector<std::unique_ptr<node>> pool;
    };

    std::string randstring(const unsigned int n, const int low = int{'a'}, const int high = int{'z'}){
        std::string _r_str(n, ' '); /* Efficient, asymptotically */
        for(char& _chr: _s_str)
            _chr = __random_range__(low, high);
        return _r_str;
    }

}


int main(){

    constexpr unsigned int n = 0xf;
    kw::linkedlist<std::string> linkedlist{};

    for(unsigned int k=0; k!=n; ++k)
        linkedlist.insert( kw::randstring( (k*2) >> 1) );
    
    kw::linkedlist<kw::linkedlist<std::vector<unsigned int>>> _ {}; /* Linked-List of Linked-List of Vector of unsigned int */

    return 0;
}