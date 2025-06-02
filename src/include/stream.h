#ifndef _STREAM
#define _STREAM

#include "decl.h"

#include <cstdio>

constexpr unsigned int __max_lines__ = BUFSIZ * BUFSIZ;

namespace kw{

    _size_t _m_memcpy(void* _to, const void* _from, const _size_t _n){
        unsigned int k{};
        while(k != _n)
            *(reinterpret_cast<unsigned char*>(_to) + k) = *(reinterpret_cast<const unsigned char*>(_from) + k);
        return k;
    }

    enum mode: unsigned int{
        CREATE  = 0b1000'0000,
        READ    = 0b0000'0001,
        WRITE   = 0b0000'0010,
        RDWR    = 0b0000'0100,
        APP     = 0b0000'1000,
    };


    template<typename __tp> struct _stream_node{
        using type = __tp;
        using key_t = unsigned int;

        explicit _stream_node(const key_t key = {}, _stream_node<__tp>* next = nullptr):
            key{ key }, next{ next } { }
        
        _stream_node(_stream_node<__tp>&& _mv_node) noexcept:
            _stream_node(_mv_node.key, _mv_node.next) {
                _mv_node.key = {}, _mv_node.next = nullptr;
            }

        key_t key;
        _stream_node<__tp>* next;
    };

    template<typename __tp> class file_stream{
        public:
            explcit file_stream(const std::string filename, mode _mode):
                _file{ nullptr }, _lines{ new (std::nothrow) _stream_node<std::string> [__max_lines__]}, _filename{ filename }, _filesize{ }, _mode{ _mode } {
                    this->_mode = _mode;
                    std::string _o_mode {};
                    if(this->_mode == mode::RDWR)
                        _o_mode.push_back('r+')
                    // TODO: handle more others
                    this->_file = fopen(this->_filename.c_str(), _o_mode);
                    establish_stream_buffer();
                }

                ~file_stream(){
                    fclose(this->_file);
                }

                void establish_stream_buffer(){
                    char* buffer = new (std::nothrow) char[BUFSIZ];
                    while(fgets(buffer, this->_file))
                        this->_lines->emplace_back(std::string{ buffer });
                    delete[] buffer;
                }

        private:
            FILE* _file;
            _stream_node<std::string>* _lines;
            const std::string _filename;
            std::string _filesize;
            unsigned int _mode;
    };

}

#endif