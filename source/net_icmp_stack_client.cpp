#include "net.h"

namespace net::icmp::stack
{

    Client::Client(net::interface::Io &interface_io, net::ipv4::stack::interface::Soft &interface_soft) : Base(interface_io, interface_soft)
    {
    }
    Code Client::send_ping(const eth::address::Custom &eth_destination, const ipv4::address::Custom &ipv4_destination)
    {
        _fill_header_eth(eth_destination);
        _fill_header_ipv4(ipv4_destination, ipv4::command::Protocol_icmp, 0x54);
        _fill_header_icmp(command::Type_request, command::Code_0, 64);

        _interface_io.transmitt(_output, 98, 100);
    }

}