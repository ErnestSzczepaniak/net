#include "net.h"

namespace net::arp::stack
{
    Client::Client(net::interface::Io & interface_io, net::ipv4::stack::interface::Soft & interface_soft) : Base(interface_io,interface_soft)
    {

    }
    Code Client::get_mac(const eth::address::Custom & eth_destination,const ipv4::address::Custom & ipv4_destination)
    {
        _clear(_output);

        _fill_header_eth(eth_destination);
        _fill_header_arp(eth_destination,ipv4_destination,command::Opcode_request);

        _interface_io.transmitt(_output, 42 , 100);

        auto size =_interface_io.receive(_input, 1000);

        if (size == -1) return Code::IO_TIMEOUT;
        if (size == 0) return Code::IO_RX;
        if (size != 64) return Code::IO_SIZE;

        if (auto code = _check_header_eth_arp(); code != Code::SUCCESS) return code;
        if (auto code = _check_header_arp_opcode(command::Opcode_replay, ipv4_destination); code != Code::SUCCESS) return code;

        return Code::SUCCESS; 

    }
}