#ifndef NET_ARP_STACK_BASE_H
#define NET_ARP_STACK_BASE_H

#include "net.h"
# include"net_ipv4_interface.h"
namespace net::arp::stack
{
    class Base
    {
        static constexpr auto size_buffer = 2048;
        public:
            Base(net::interface::Io & io, net::ipv4::stack::interface::Soft & soft);
        protected:

        void _clear(unsigned char * buffer);

        void _fill_header_eth(const eth::address::Custom & destination);
        void _fill_header_arp(const eth::address::Custom & eth_destination, const ipv4::address::Custom & ipv4_destination, unsigned short int opcode);
    
        Code _check_header_eth_arp();
        Code _check_header_arp(const ipv4::address::Custom & ipv4_destination);
        Code _check_header_arp_opcode(unsigned short int opcode, const ipv4::address::Custom & ipv4_destination);

        unsigned char _input[size_buffer];
        unsigned char _output[size_buffer];

        net::interface::Io & _interface_io;
        net::ipv4::stack::interface::Soft & _interface_soft;
    };
};


#endif