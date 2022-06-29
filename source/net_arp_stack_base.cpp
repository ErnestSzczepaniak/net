
#include "net.h"
namespace net::arp::stack
{
    Base::Base(net::interface::Io & io,net::ipv4::stack::interface::Soft & soft) : _interface_io(io),_interface_soft(soft)
    {
        _clear(_output);
    }

    void Base:: _clear(unsigned char * buffer)
    {
        memset(buffer, 0, size_buffer);
    }
    void Base::_fill_header_eth(const eth::address::Custom & destination)
    {
        auto header_eth = eth::Header(_output);

        header_eth.destination = destination;
        header_eth.source = _interface_io.address();
        header_eth.type = eth::type::Arp;
    }
    void Base::_fill_header_arp(const eth::address::Custom & eth_destination,const ipv4::address::Custom & ipv4_destination, unsigned short int opcode)
    {
        auto header_arp = arp::Header(_output);

        header_arp.hardware_type = net::arp::command::Hardware_type_ethernet;
        header_arp.protocol_type = net::arp::command::Protocol_type_ipv4;

        header_arp.hardware_size = net::arp::command::Hardware_size_ethernet;
        header_arp.protocol_size = net::arp::command::Protocol_size_ipv4;

        header_arp.opcode = opcode;

        header_arp.sender_mac = _interface_io.address();
        header_arp.sender_ipv4 = _interface_soft.address();
        header_arp.target_mac = eth_destination;
        header_arp.target_ipv4 = ipv4_destination;

    }
    Code Base::_check_header_eth_arp()
    {
        auto header_eth = eth::Header(_input);

        if (header_eth.destination != eth::address::Broadcast && header_eth.destination != _interface_io.address() && header_eth.destination != eth::address::Empty) 
            return Code::HEADER_ETH_ADDRESS_DESTINATION;
        if (header_eth.type != eth::type::Arp)
            return Code::HEADER_ETH_TYPE;

        return Code::SUCCESS;
    }
    Code Base::_check_header_arp_opcode(unsigned short int opcode, const ipv4::address::Custom & ipv4_destination)
    {
        auto header_arp = arp::Header(_input);

        if (header_arp.opcode != opcode)
            return Code::HEADER_ARP_OPCODE;
    }
    Code Base::_check_header_arp(const ipv4::address::Custom & ipv4_destination)
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
        if (header_arp.sender_ipv4 != ipv4_destination)
            return Code::HEADER_ARP_SENDER_IP;
        if (header_arp.target_mac != net::eth::address::Empty)
            return Code::HEADER_ARP_TARGET_MAC;
        if (header_arp.target_ipv4 != _interface_soft.address())
            return Code::HEADER_ARP_TARGET_IP;

        return Code::SUCCESS;
    }
}