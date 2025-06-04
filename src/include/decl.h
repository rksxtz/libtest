#ifndef _DECL
#define _DECL

#include <new>

using _size_t = unsigned int;
using _ssize_t = signed long int;

template<typename __tp> using _ptr = __tp*;
template<typename __tp> using _c_ptr = const _ptr<__tp>;


namespace kw{

    _size_t _m_memcpy(void*, const void*, _size_t);

    _ssize_t strcmp(const void*, const void*);

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


}


#endif