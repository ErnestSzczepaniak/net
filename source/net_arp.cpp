#include "net.h"

namespace net::arp
{
    void Base::_fill_header_eth(const eth::address::Custom & destination)
    {
        auto header_eth = eth::Header(_output);

        header_eth.destination = destination;
        header_eth.source = _interface_io.address();
        header_eth.type = eth::type::Arp;
    }
    void net::arp::Base::_fill_header_arp(const eth::address::Custom & eth_destination,const ipv4::address::Custom & ipv4_destination, unsigned short int opcode)
    {
        auto header_arp = arp::Header(_output);

        header_arp.hardware_type = net::arp::command::Hardware_type_ethernet;
        header_arp.protocol_type = net::arp::command::Protocol_type_ipv4;

        header_arp.hardware_size = net::arp::command::Hardware_size_ethernet;
        header_arp.protocol_size = net::arp::command::Protocol_size_ipv4;

        header_arp.opcode = opcode;

        header_arp.sender_mac = _interface_io.address();
        header_arp.sender_ipv4 = net::ipv4::address::Babe;

        header_arp.target_mac = eth_destination;
        header_arp.target_ipv4 = ipv4_destination;

    }
    Code net::arp::Base::_check_header_eth_arp()
    {
        auto header_eth = eth::Header(_input);

        if (header_eth.destination != eth::address::Broadcast && header_eth.destination != _interface_io.address()) 
            return Code::HEADER_ETH_ADDRESS_DESTINATION;
        if (header_eth.type != eth::type::Arp)
            return Code::HEADER_ETH_TYPE;

        return Code::SUCCESS;
    }
    Code net::arp::Base::_check_header_arp_opcode(unsigned short int opcode)
    {
        auto header_arp = arp::Header(_input);

        if (header_arp.hardware_type != command::Hardware_type_ethernet) 
            return Code::HEADER_ARP_HARDWARE_TYPE;
        if (header_arp.protocol_type != command::Protocol_type_ipv4) 
            return Code::HEADER_ARP_PROTOCOL_TYPE;
        if (header_arp.hardware_size != command::Hardware_size_ethernet) 
            return Code::HEADER_ARP_HARDWARE_SIZE;
        if (header_arp.protocol_size != command::Protocol_size_ipv4) 
            return Code::HEADER_ARP_PROTOCOL_SIZE;
        if (header_arp.opcode != opcode)
            return Code::HEADER_ARP_OPCODE;

        return Code::SUCCESS;
    }
    Code Arp::process()
    {
        auto size = _interface_io.receive(_input, 0);

        if (size == -1) return Code::IO_TIMEOUT;
        if (size == 0) return Code::IO_RX;
        if (auto code = _check_header_eth_arp(); code != Code::SUCCESS) return code;
        if (auto code = _check_header_arp_opcode(command::Opcode_replay); code != Code::SUCCESS) return code;
        if (auto code = _check_header_arp_opcode(command::Opcode_request); code != Code::SUCCESS) return code;

        auto size_tx = 0;

        _fill_header_eth(eth::Header(_input).source);

        if (arp::Header(_input).opcode == net::arp::command::Opcode_request)
        {
            _fill_header_arp(arp::Header(_input).sender_mac,arp::Header(_input).sender_ipv4,command::Opcode_replay);
            size_tx = 42;
        }
        else if (arp::Header(_input).opcode == net::arp::command::Opcode_replay)
        {
           
        }

        if (_interface_io.transmitt(_output, size_tx, 100) != size_tx) return Code::IO_TX;

        _clear(_output);

        return Code::SUCCESS;
    }
}
void net::arp::Base:: _clear(unsigned char * buffer)
{
    memset(buffer, 0, size_buffer);
}