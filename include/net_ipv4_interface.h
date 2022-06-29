#ifndef NET_IPV4_INTERFACE
#define NET_IPV4_INTERFACE

#include "net.h"

namespace net::ipv4::stack::interface
{
    class Soft
    {
        public:
            virtual net::ipv4::address::Custom & address() = 0;
    };
}; 

#endif