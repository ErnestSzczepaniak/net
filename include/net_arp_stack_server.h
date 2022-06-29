#ifndef NET_ARP_STACK_SERVER_H
#define NET_ARP_STACK_SERVER_H

#include "net.h"
#include "net_ipv4_interface.h"
namespace net::arp::stack
{
    class Server : public Base
    {
        public:
            Server(net::interface::Io & interface_io, net::ipv4::stack::interface::Soft & interface_soft);
            Code process();
        private:
    };
}

#endif