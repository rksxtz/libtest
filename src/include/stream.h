#ifndef _STREAM_H_
#define _STREAM_H_

#include <cstdio>

#include <string>
#include <vector>

#define BUFFERING 0b00000001
#define NOBUFFERING 0b10000000

#define STREAM_READY 0b00000010
#define STREAM_BUSY 0b01000000
#define STREAM_ERROR 0b00001000


namespace kw{

    template<typename __tp> struct stream_block_node{
        public:
            using node = stream_block_node<__tp>;
            using size_type = unsigned int;

            explicit stream_block_node(const size_type size = 8):
                next{ nullptr }, size{ size } { }
    
            node* next;
            size_type size;
    };

    template<typename __tp> class stream{
        public:
            using node = stream_block_node<__tp>;
            using node_ptr = node*;

            explicit stream(const std::string& filename):
                pool{ new (std::nothrow) std::vector<node_ptr>{} }, _associated_file{ fopen(filename.c_str(), "rb+") },
                mask{ 0x0 } {
                    if(this->_associated_file)
                        this->mask |= (BUFFERING | STREAM_READY);
                    else
                        this->mask |= (STREAM_ERROR | STREAM_BUSY | NOBUFFERING);
                }


            ~stream() {
                for(const node_ptr node: (*this->pool))
                    delete node;
                delete this->pool;
                fclose(this->_associated_file);
            }


        private:
            std::vector<kw::stream_block_node<__tp>*> pool;
            FILE* _associated_flie;
            unsigned int mask;
    };

}


#endif