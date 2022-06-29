#ifndef NET_ICMP_STACK_CLIENT_H
#define NET_ICMP_STACK_CLIENT_H

#include "net.h"
#include "net_ipv4_interface.h"

namespace net::icmp::stack
{
    class Client : public Base
    {
        public:
            Client(net::interface::Io & interface_io, net::ipv4::stack::interface::Soft & interface_soft);
            Code send_ping(const eth::address::Custom & eth_destination,const ipv4::address::Custom & ipv4_destination);
    };
}

#endif