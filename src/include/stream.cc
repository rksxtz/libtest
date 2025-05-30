#include "stream.h"
#include "logger.h"

#include <vector>

#include <iostream>

kw::logger _logger{"stream_cc.log"};

#define __log__(_s_msg) (_logger.write(_s_msg, __FUNCTION__))
#define __llog__() (_logger.last_log())


int main(){

    kw::stream<unsigned int> stream{};
    __log__("Created an instance of kw::stream<__tp> with __tp = unsigned int [" + std::to_string(1) + "]");

    stream.associate("../../README.md", kw::mode_t::RW_OPEN);

    if(stream.opened())
        std::cout << "opened \"../../README.md\", successfully, using kw::stream<unsigned int>.\n";
    
    const std::string content { stream.fetch_string() };

    std::cout << "README.md : \n" << content << '\n';

    __log__("Exiting \"stream.cc\"...");

    return 0;
}