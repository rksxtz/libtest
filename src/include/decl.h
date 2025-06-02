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

        void* allocate(const unsigned int n){
            return ::operator new(n);
        }

        void deallocate(void* _buffer){
            ::operator delete(_buffer);
        }

        void* _memcpy(void* _t_buffer, const void* _f_buffer, const unsigned int n){
            _size_t _cnt{};
            void* _bf_holder = _t_buffer;
            while(_cnt != n)
                *(reinterpret_cast<unsigned char*>(_t_buffer) + _cnt) = *(reinterpret_cast<const unsigned char*>(_f_buffer) + _cnt),
                ++_cnt;
            return _bf_holder;
        }

    }


}


#endif