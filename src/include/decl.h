#ifndef _DECL
#define _DECL

#include <new>
#include <sys/stat.h>

#include <string>
#include <vector>
#include <utility>

#include <iostream>


using _size_t = unsigned int;
using _sgnsize_t = signed long int;

using _file_size_t = unsigned long long int;

template<typename __tp> using _ptr = __tp*;
template<typename __tp> using _c_ptr = const _ptr<__tp>;

#define _debug_error(message) std::cerr << message << '\n' << std::flush


namespace kw{

    _size_t _m_memcpy(void*, const void*, _size_t);

    _sgnsize_t strcmp(const void*, const void*);

    enum class mode;


    namespace buffer{

        /**
         * @brief allocates n bytes of raw memory, using the global operator new
         * 
         * @param n 
         * @return void* 
         */
        void* _m_allocate(const unsigned int n){
            return ::operator new(n);
        }

        /**
         * @brief deallocates the memory, whose first block is pointed to by _buffer
         * precondition: the _buffer shall be previously allocated using kw::buffer::_m_allocate() or sole operator new().
         * 
         * @param _buffer 
         */
        void _m_deallocate(void* _buffer){
            ::operator delete(_buffer);
        }

        /**
         * @brief custom memory copy subroutine
         * precondition: both the memory locations, as provided, shall have valid n bytes region, from the start
         * 
         * @param _t_buffer 
         * @param _f_buffer 
         * @param n 
         * @return void* 
         */
        void* _memcpy(void* _t_buffer, const void* _f_buffer, const unsigned int n){
            _size_t _cnt{};
            void* _bf_holder = _t_buffer;
            while(_cnt != n)
                *(reinterpret_cast<unsigned char*>(_t_buffer) + _cnt) = *(reinterpret_cast<const unsigned char*>(_f_buffer) + _cnt),
                ++_cnt;
            return _bf_holder;
        }

        /**
         * @brief custom memory move subroutine
         * precondition: similar to, kw::buffer::_memcpy, both the buffer shall have valid n bytes of region, in the memory
         * 
         * @param _t_buffer 
         * @param _f_buffer 
         * @param n 
         * @return void* 
         */
        void* _memmove(void* _t_buffer, void* _f_buffer, const unsigned int n){
            _size_t _cnt{};
            while(_cnt != n)
                *(reinterpret_cast<unsigned char*>(_t_buffer) + _cnt) = static_cast<unsigned char&&>(
                    *(reinterpret_cast<unsigned char*>(_f_buffer) + _cnt))
                , ++_cnt;
        }

    }

    /**
         * @brief fetches the file-size, with appropriate units, making use of sys/stat.h
         * 
         * @param filename 
         * @return std::string 
         */
        std::string _file_size(const std::string& filename){
            struct stat _stat;
            if(!stat(filename.c_str(), &_stat)){
                _file_size_t _sz = _stat.st_size;
                const char* units[] = { "B", "KB", "MB", "GB" };
                unsigned int _uindex{};
                long double _db_sz = static_cast<long double>(_sz);
                while(_db_sz > 1024.0 && _uindex < 3)
                    _db_sz /= 1024.0, _uindex++;
                return std::string{ std::to_string(_db_sz) + " " + std::string{units[_uindex]} };
            } _debug_error("Error fetching stat for " + filename + ".");
        }

}

class allocator{
    public:
        using size_t = std::size;
        explicit allocator():
            _m_pool{ }, _m_allco_bytes{ }, _m_pool_length{ } { }
        
        void* allocate(size_t n){
            void* _r_ptr = kw::buffer::_m_allocate(n);
            this->_m_pool.push_back( std::pair<size_t, void*>{ n, _r_ptr } );
            this->_m_alloc_bytes += n;
            this->_m_pool_length = this->_m_pool.size();
            return _r_ptr;
        }

        void deallocate(const unsigned int offset = 0){
            if(offset){
                std::pair<size_t, void*> _m_mem_pair = this->_m_pool[offset];
                this->_m_pool.erase( this->_m_pool.begin() + offset );
                this->_m_alloc_bytes -= _m_mem_pair.first, --this->_m_pool_length;
                kw::buffer::_m_deallocate(_m_mem_pair.second);
            }else{

            }
        }

    private:
        std::vector<std::pair<size_t, void*>> _m_pool;
        size_t _m_alloc_bytes;
        size_t _m_pool_length;
};


#endif