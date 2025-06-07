#include <limits>
#include <type_traits>
#include <experimental/random>

#include "include/decl.h"

#include <iostream>



#define __minof__(__tp__) std::numeric_limits<__tp__>::min()
#define __maxof__(__tp__) std::numeric_limits<__tp__>::max()

#define __random_range__(low, high) std::experimental::randint(low, high)
#define __random__() __random_range__(int{__minof__(signed char)}, int{__maxof__(unsigned char)})



template<typename __tp> std::vector<__tp> randomized_vector(const unsigned int n){
    std::vector<__tp> rv(n);
    for(__tp& element: rv)
        element = __random__();
    return static_cast<std::vector<__tp>&&>(rv);
}

template<typename __tp> std::ostream& operator<< (std::ostream& __ost, const std::vector<__tp>& vector){
    __ost << "[&=" << &vector << " -> [" << vector.data() << " (" << vector.size() << ")]] : ";
    if(!vector.empty())
        for(unsigned int k=0; k!=vector.size(); ++k)
            __ost << (!k ? "[" : "") << vector[k] << (k==vector.size() -1 ? "]" : ", ");
    return __ost;
}


int main(const int argc, const char* argv[]){

    std::cout << "filesize(this) : " << kw::_file_size("main.cc") << "\n";

    return 0;
}