#include <cstdio>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sys/types.h>

#include <memory>
#include <chrono>
#include <concepts>

#include <cstring>

#include <ios>
#include <sstream>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")


int main(const int argc, const char* argv[]) {
#if defined(__GNUC__) && defined(_WIN32)
    std::ios_base::sync_with_stdio( false );

    WSADATA wsa;
    SOCKET sock;
    if (!WSAStartup(MAKEWORD(2,2), &wsa)) {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET)
            std::cout << "Established socket [&=" << &sock << "], [UID = " << sock << "]\n";
        std::unique_ptr<addrinfo> _lm_addrinfo_handle{ new (std::nothrow) addrinfo };
        addrinfo* _lm_addrinfo{ _lm_addrinfo_handle.get() };
        addrinfo* _res_addrinfo = nullptr;
        memset(_lm_addrinfo, 0, sizeof(addrinfo));
        _lm_addrinfo->ai_family = AF_INET;
        _lm_addrinfo->ai_socktype = SOCK_STREAM;
        if (! (getaddrinfo(nullptr, "1200", _lm_addrinfo, &_res_addrinfo)) ) {
            if (_res_addrinfo) {
                char buffer[1024];
                inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in*>(_res_addrinfo->ai_addr)->sin_addr, buffer, 1024);
                const std::string _lm_ipv4_addr{ buffer };
                const unsigned int _bound_port { ntohs(reinterpret_cast<sockaddr_in*>(_res_addrinfo->ai_addr)->sin_port) };
                const std::string _nt_lm_ipv4_addr{ _lm_ipv4_addr + ":" + std::to_string( _bound_port ) };
                std::cout << "Local IPv4 address : " << _lm_ipv4_addr << "\n\tNT [Socket-Bound] : " << _nt_lm_ipv4_addr << '\n';
                freeaddrinfo(_res_addrinfo);
            }else std::cout << "Could not find a suitable IPv4 address of local-machine\n";
        } else std::cout << "Error fetching Local Machine Address [AF_INET, SOCK_STREAM, loopback-addr]\n";
    }
    closesocket(sock);
    WSACleanup();
#else
    #warning "<?>"
#endif
    return 0;
}
