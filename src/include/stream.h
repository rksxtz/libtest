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

    enum class mode_t: unsigned char{
        R_OPEN      = 0x1, 
        W_OPEN      = 0x1 << 1, 
        RW_OPEN     = 0x1 << 2, 
        APP_OPEN    = 0x1 << 3,
        CREATE      = 0x1 << 7
    };

    constexpr unsigned char operator& (const mode_t& a, const mode_t& b) {
        return static_cast<unsigned char>(a) & static_cast<unsigned char>(b);
    }

    template<typename __tp> class stream{
        public:
            using node = stream_block_node<__tp>;
            using node_ptr = node*;

            explicit stream():
                pool{} {
                }

            explicit stream(const std::string& filename):
                pool{ new (std::nothrow) std::vector<kw::stream_block_node<__tp>*>{} },
                mask{ 0x0 } {
                    if(this->_associated_file)
                        this->mask |= (BUFFERING | STREAM_READY);
                    else
                        this->mask |= (STREAM_ERROR | STREAM_BUSY | NOBUFFERING);
                }


            ~stream() {
                for(const kw::stream_block_node<__tp>* node: (*this->pool))
                    delete node;
                delete this->pool;
                fclose(this->_associated_file);
            }

            std::string parse_mode(const mode_t& mode) {
                std::string smode {};
                if(mode & mode_t::RW_OPEN)
                    smode += "r+";
                else if(mode & mode_t::R_OPEN)
                    smode.push_back('r');
                else if(mode & mode_t::W_OPEN)
                    smode.push_back('w');
                else if(mode & mode_t::APP_OPEN)
                    smode.push_back('a');
                if(mode & mode_t::CREATE)
                    smode.push_back('+');
                return static_cast<std::string&&>(smode);
            }

            void associate(const std::string& filename, const mode_t& mode) noexcept {
                if(!filename.empty()) {
                    this->_associated_file = fopen(filename.c_str(), parse_mode(mode).c_str());
                    if(this->_associated_file)
                        this->mask |= (BUFFERING | STREAM_READY);
                    else this->mask |= (STREAM_ERROR | STREAM_BUSY | NOBUFFERING);
                }
            }

            void dissociate(){
                if(this->_associated_file){
                    fclose(this->_associated_file);
                    this->mask = {};
                }
            }

            bool opened(){
                return this->_associated_file;
            }

            std::string fetch_string(const bool full = true) noexcept {
                if(this->_associated_file){
                    std::string rv{};
                    char ch{};
                    while((ch = getc(this->_associated_file)) != EOF)
                        rv.push_back(ch);
                    return static_cast<std::string&&>(rv);
                } return {};
            }


        private:
            std::vector<kw::stream_block_node<__tp>*>* pool;
            FILE* _associated_file;
            unsigned int mask;
    };

}


#endif