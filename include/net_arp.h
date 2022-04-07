#ifndef net_arp_h
#define net_arp_h
#include "net.h"
#include "net_ipv4.h"
#include "net_arp_code.h"
#include "net_bitfield.h"
#include "net_bytefield.h"


namespace net::arp
{
    namespace command
    {
        static constexpr unsigned short int Hardware_type_ethernet = 0x0001;
        static constexpr unsigned short int Protocol_type_ipv4 = 0x0800; 
        static constexpr unsigned char Hardware_size_ethernet = 0x06;
        static constexpr unsigned char Protocol_size_ipv4 = 0x04;
        static constexpr unsigned short int Opcode_request = 0x0001;
        static constexpr unsigned short int Opcode_replay = 0x0002;
    };
    class Base
    {
        static constexpr auto size_buffer = 42;
        public:
            Base(net::interface::Io & io);
        protected:

        void _clear(unsigned char * buffer);

        void _fill_header_eth(const eth::address::Custom & destination);
        void _fill_header_arp(const eth::address::Custom & eth_destination, const ipv4::address::Custom & ipv4_destination, unsigned short int opcode);
    
        Code _check_header_eth_arp();
        Code _check_header_arp_opcode(unsigned short int opcode);

        unsigned char _input[size_buffer];
        unsigned char _output[size_buffer];

        net::interface::Io & _interface_io;
    };
    class Header
    {
        using Hardware_type = Bytefield<unsigned short int, 0>;
        using Protocol_type = Bytefield<unsigned short int , 2>;

        using Hardware_size = Bytefield<unsigned char, 4>;
        using Protocol_size = Bytefield<unsigned char, 5>;

        using Opcode = Bytefield<unsigned short int, 6>;

        using Sender_mac = Bytefield<eth::address::Custom, 8, false>;
        using Sender_ipv4 = Bytefield<ipv4::address::Custom, 14, false>;

        using Target_mac = Bytefield<net::eth::address::Custom, 18, false>;
        using Target_ipv4 = Bytefield<net::ipv4::address::Custom, 24, false>;
    public:
        Header(unsigned char * data):
            hardware_type(data+position), protocol_type(data+position), hardware_size(data+position), protocol_size(data+position), opcode(data+position), sender_mac(data+position),
            sender_ipv4(data+position), target_mac(data+position), target_ipv4(data+position){}
        ~Header(){}
        Hardware_type hardware_type;
        Protocol_type protocol_type;
        Hardware_size hardware_size;
        Protocol_size protocol_size;
        Opcode opcode;

        Sender_mac sender_mac;
        Sender_ipv4 sender_ipv4;

        Target_mac target_mac;
        Target_ipv4 target_ipv4;
        
        static constexpr auto position = 14;
        static constexpr auto size = 28;   
    };
    class Arp : public Base
    {
        public:
            Arp(net::interface::Io & io, interface::Io & server);
            Arp();
            Code process();
    };

    
};
#endif