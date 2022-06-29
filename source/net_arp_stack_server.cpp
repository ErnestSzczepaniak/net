#include "net.h"
#include "net_ipv4_interface.h"
namespace net::arp::stack
{
    Server::Server(net::interface::Io & interface_io, net::ipv4::stack::interface::Soft & interface_soft)
    : Base(interface_io,interface_soft)
    {

    }
    Code Server::process()
    {
        auto size = _interface_io.receive(_input, 0);

        if (size == -1) return Code::IO_TIMEOUT;
        if (size == 0) return Code::IO_RX;
        if (auto code = _check_header_eth_arp(); code != Code::SUCCESS) return code;
        if (auto code = _check_header_arp(arp::Header(_input).sender_ipv4); code != Code::SUCCESS) return code;

        auto size_tx = 0;

        _fill_header_eth(eth::Header(_input).source);

        if (arp::Header(_input).opcode == net::arp::command::Opcode_request)
        {
            _fill_header_arp(arp::Header(_input).sender_mac,arp::Header(_input).sender_ipv4,command::Opcode_replay);
            size_tx = 42;
        }
        else if (arp::Header(_input).opcode == net::arp::command::Opcode_replay)
        {
           /*Wpisanie do tablicy arp adresu MAC*/
        }

        if (_interface_io.transmitt(_output, size_tx, 100) != size_tx) return Code::IO_TX;

        _clear(_output);

        return Code::SUCCESS;
    }
}
