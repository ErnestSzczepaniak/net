#ifndef NET_ICMP_SERVER_H_
#define NET_ICMP_SERVER_H_

#include "net.h"
#include "net_ipv4_interface.h"

namespace net::icmp::stack
{
   class Server : public Base
    {
        public:
            Server(net::interface::Io & interface_io, net::ipv4::stack::interface::Soft & interface_soft);
            net::ipv4::stack::Code process();
        private:
    };
}


#endif