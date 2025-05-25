#include <new>
#include <experimental/random>

#include <iostream>


#define __RANDOM_RANGE(LOW, HIGH) std::experimental::randint(LOW, HIGH)


namespace eff {

    template<typename __tp> void
    __swap(__tp& A, __tp& B) {
        __tp aux { static_cast<__tp&&>(A) };
        A = static_cast<__tp&&>(B);
        B = static_cast<__tp&&>(aux);
    }

    unsigned int parent(const unsigned int nodeindex) { return nodeindex / 2 - (!(nodeindex&1) ? 1 : 0); }
    unsigned int left(const unsigned int nodeindex) { return (nodeindex << 1) + 1; }
    unsigned int right(const unsigned int nodeindex) { return (nodeindex << 1 ) + 1 + 1; }


    template<typename __tp> void
    heapify(__tp* __base, const unsigned int& length, const unsigned int& heapsize, const unsigned int nodeindex) {
        if (__base) {
            unsigned int largest = nodeindex;
            const unsigned int left = eff::left(nodeindex);
            const unsigned int right = eff::right(nodeindex);
            if (left < heapsize && __base[left] > __base[largest])
                largest = left;
            if (right < heapsize && __base[right] > __base[largest])
                largest = right;
            if (largest != nodeindex) {
                __swap(__base[largest], __base[nodeindex]);
                heapify(__base, length, heapsize, largest);
            }
        }
    }


    template<typename __tp> void
    buildmaxheap(__tp* __base, const unsigned int& length, const unsigned int& heapsize) {
        if (__base) {
            signed int nodeindex = static_cast<signed int>(length) / 2;
            while (nodeindex != -1)
                eff::heapify(__base, length, heapsize, nodeindex--);
        }
    }


    template<typename __tp> void
    sort(__tp* __base, const unsigned int& length, unsigned int& heapsize) {
        eff::buildmaxheap(__base, length, heapsize);
        signed int nodeindex = static_cast<signed int>(length)-1;
        while (nodeindex) {
            __swap<__tp>(__base[0], __base[nodeindex]);
            nodeindex--, heapsize--;
            eff::heapify<__tp>(__base, length, heapsize, 0);
        }
        heapsize = length;
    }



    template<typename __tp> void
    show(const __tp* __base, const unsigned int& length, const unsigned int& heapsize, std::ostream& __ost) {
        __ost << "[&=" << &__base << " -> [" << __base << " ... " << __base + (length-1) << "]] : ";
        for (unsigned int k=0; k!=heapsize; ++k)
            __ost << (!k ? "[" : "") << __base[k] << (k==heapsize-1 ? "]\n" : ", ");
    }

}



int main() {
    constexpr unsigned int length = 0xf;
    unsigned int heapsize {};
    void* buffer = new (std::nothrow) char[2048];

    unsigned int* __base = new (buffer) unsigned int[length];
    while (heapsize != length)
        __base[heapsize++] = __RANDOM_RANGE(0x0, 0xff);

    eff::show<unsigned int>(__base, length, heapsize, std::cout);
    eff::buildmaxheap<unsigned int>(__base, length, heapsize);
    eff::show<unsigned int>(__base, length, heapsize, std::cout);
    eff::sort<unsigned int>(__base, length, heapsize);
    eff::show<unsigned int>(__base, length, heapsize, std::cout);

    delete[] reinterpret_cast<const char*>(buffer);
    return 0;
}