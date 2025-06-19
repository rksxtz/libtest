#include <memory>

#include <vector>

#include <ostream>
#include <iostream>


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
                _m_sentinel{ std::unique_ptr<node>{ new (std::nothrow) node{ {}, nullptr, nullptr } } }, nil{ nullptr },
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

            void insert(node* node){
                node->next = this->nil->next;
                this->nil->next->prev = node;
                this->nil->next = node, node->prev = this->nil;
                this->head = node;
                this->pool.emplace_back( std::unique_ptr<node>{ node } );
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

}


int main(){
    return 0;
}