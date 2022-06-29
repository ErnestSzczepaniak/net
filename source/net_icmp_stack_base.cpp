#include "net.h"

namespace net::icmp::stack
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
        header_eth.type = eth::type::Ipv4;
    }
    void Base::_fill_header_ipv4(const ipv4::address::Custom & ipv4_destination, unsigned char protocol, unsigned char size)
    {
        auto header_ipv4 = ipv4::Header(_output);

        header_ipv4.version = ipv4::command::Version_4;
        header_ipv4.header_length = net::ipv4::command::Header_length_20;
        header_ipv4.differentiated_services_codepoint = net::ipv4::command::Different_services_codepoint_default;
        header_ipv4.explicit_congestion_notification = net::ipv4::command::Explicit_congestion_notfication_not_ecn_capable_transport;
        header_ipv4.total_length = size;
        header_ipv4.identification = 0xf4ee; // Tutaj wpisana jest na sztywno wartość losowa można tutaj wpisywać jakkolwiek. 
        header_ipv4.reserved_bit = net::ipv4::command::Reserved_bit_not_set;
        header_ipv4.donot_fragment = net::ipv4::command::Do_not_fragment_set;
        header_ipv4.more_fragments = net::ipv4::command::More_framgent_not_set;
        header_ipv4.fragment_offset = net::ipv4::command::Fragment_offset_0;
        header_ipv4.protocol = net::ipv4::command::Protocol_icmp;
        header_ipv4.checksum = 0x0000; //przed przeliczeniem chcsum trzeba wyzerować to pole
        header_ipv4.source = _interface_soft.address();
        header_ipv4.target = ipv4_destination;
        unsigned short int * ptr =(unsigned  short int *) &_output[14]; // numer w tablicy 14 bo od tego pola zaczyna się nagłowek IP
        header_ipv4.checksum = net::ipv4::Header::Calc_checksum((unsigned  short int *)ptr, 20); // size 20 bo tyle zajmuje nagłowek IP
    }
    void Base::_fill_header_icmp(unsigned char type, unsigned char code, unsigned short identifier, unsigned short sequence_number,  unsigned short size)
    {
        auto header_icmp = icmp::Header(_output);

        header_icmp.type = type;
        header_icmp.code = code;
        header_icmp.checksum = 0x0000;
        header_icmp.identifier = identifier; 
        header_icmp.sequence_number = sequence_number;
        header_icmp.timestamp = 0x5b7d5e6200000000; // jest to wartość losowa wpisana na stałe powinnien tutaj być znacznik czasu informujacy kiedy został wysłany pakiet
        header_icmp.checksum = net::ipv4::Header::Calc_checksum((unsigned short int *)&_output[34], size); // liczenie chceck sumy od pola 34 bo tam zaczyna się nagłowek ICMP. adresy w buforze 0-13 nagłowek eth, 14-33 nagłwoek ipv4, 34 do wartosci jaką ma padding w nagłówku ICMP. 

    }
    /* przeciążona metoda głownie do testów ze sztywnymi parametrami indetyficator czy sequence_number i timestamp */
    void Base::_fill_header_icmp(unsigned char type, unsigned char code, unsigned short size)
    {
        auto header_icmp = icmp::Header(_output);

        header_icmp.type = type;
        header_icmp.code = code;
        header_icmp.checksum = 0x0000;
        header_icmp.identifier = 0x3ca5;
        header_icmp.sequence_number = 0x01;
        header_icmp.timestamp = 0x5b7d5e6200000000;
        header_icmp.checksum = net::ipv4::Header::Calc_checksum((unsigned short int *)&_output[34], size);
    }

}