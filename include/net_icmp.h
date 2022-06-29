#ifndef NET_ICMP_H
#define NET_ICMP_H

#include "net.h"


namespace net::icmp
{
    namespace command
    {
        static constexpr unsigned char Type_request = 0x08;
        static constexpr unsigned char Type_replay = 0x00;
        static constexpr unsigned char Code_0 = 0x00;
    };
    class Header
    {
        using Type = Bytefield<unsigned char, 0>;
        using Code = Bytefield<unsigned char, 1>;
        using Checksum = Bytefield<unsigned short int, 2>;
        using Identifier = Bytefield<unsigned short int, 4>;
        using Sequence_number = Bytefield<unsigned short int, 6>;
        using Timestamp = Bytefield<unsigned long long, 8>;
        using Data_padding = Bytefield<unsigned char, 16>;

        public:
            Header(unsigned char * data, int size = 48) : 
            type(data+position),
            code(data+position),
            checksum(data+position),
            identifier(data+position),
            sequence_number(data+position),
            timestamp(data+position),
            data_pading(data+position)
            {}

            Type type;
            Code code;
            Checksum checksum;
            Identifier identifier;
            Sequence_number sequence_number;
            Timestamp timestamp;
            Data_padding data_pading;

            static constexpr auto position = 34;
            int size;
    };
}

#endif
