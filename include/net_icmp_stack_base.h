#ifndef NET_ICMP_STACK_BASE_H_
#define NET_ICMP_STACK_BASE_H_

#include "net.h"
# include"net_ipv4_interface.h"

namespace net::icmp::stack
{
    class Base
    {
        static constexpr auto size_buffer = 2048;
        public:
            Base(net::interface::Io & io, net::ipv4::stack::interface::Soft & soft);
        protected:

        void _clear(unsigned char * buffer);

        void _fill_header_eth(const eth::address::Custom & destination);
        void _fill_header_ipv4(const ipv4::address::Custom & ipv4_destination, unsigned char protocol,unsigned char size);
        void _fill_header_icmp(unsigned char type, unsigned char code, unsigned short identifier, unsigned short sequence_number,  unsigned short size);
        void _fill_header_icmp(unsigned char type, unsigned char code, unsigned short size);
    
        Code _check_header_eth_ipv4();
        Code _check_header_ipv4(const ipv4::address::Custom & ipv4_destination);
        Code _check_header_icmp();

        unsigned char _input[size_buffer];
        unsigned char _output[size_buffer];

        net::interface::Io & _interface_io;
        net::ipv4::stack::interface::Soft & _interface_soft;
    };
};

#endif