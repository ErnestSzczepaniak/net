#ifndef NET_ARP_STACK_CLIENT_H
#define NET_ARP_STACK_CLIENT_H

#include "net.h"
#include "net_ipv4_interface.h"
namespace net::arp::stack
{
    class Client : public Base
    {
        public:
            Client(net::interface::Io & interface_io, net::ipv4::stack::interface::Soft & interface_soft);
            Code get_mac(const eth::address::Custom & eth_destination,const ipv4::address::Custom & ipv4_destination);
    };
}

#endif