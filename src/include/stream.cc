#include "stream.h"

#include <vector>

#include <iostream>


int main(){

    kw::stream<unsigned int> stream{};

    stream.associate("../../README.md", kw::mode_t::RW_OPEN);

    if(stream.opened())
        std::cout << "opened \"../../README.md\", successfully, using kw::stream<unsigned int>.\n";
    
    const std::string content { stream.fetch_string() };

    std::cout << "README.md : \n" << content << '\n';

    return 0;
}