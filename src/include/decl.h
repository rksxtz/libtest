#ifndef _DECL
#define _DECL


using _size_t = unsigned int;
using _ssize_t = signed long int;

template<typename __tp> using _ptr = __tp*;
template<typename __tp> using _c_ptr = const _ptr<__tp>;


namespace kw{

    _size_t _m_memcpy(void*, const void*, _size_t);

    enum class mode;


}


#endif