#ifndef net_ipv4_h
#define net_ipv4_h
#include "net.h"
#include "net_ipv4.h"
#include "net_bitfield.h"
#include "net_bytefield.h"

namespace net::ipv4
{
    namespace address
    {
        class Custom
        {
            public:
            Custom() {}
            Custom(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
            {
                value[0] = a;
                value[1] = b;
                value[2] = c;
                value[3] = d;
            }
            ~Custom() {}
            void operator=(const Custom & other)
            {
                memcpy(value, &other.value, 4);
            }
            bool operator==(const Custom & other)
            {
                if(memcmp(value, other.value, 4)==0)
                    return true;
                else
                    return false;
            }
            unsigned char value[4];
        };
        static Custom Broadcast = Custom(0xff,0xff,0xff,0xff);
        static Custom Babe = Custom(0x01,0x02,0x03,0x04);
        static Custom Target = Custom(0x01,0x02,0x03,0x05);
 
    };
    class Header
    {

        using Version = Bitfield<unsigned char, 0, 4, 4>;
        using Header_length = Bitfield<unsigned char, 0, 0, 4>;
        using Differentiated_services_codepoint = Bitfield<unsigned char, 1 ,2 ,6>;
        using Explicit_congestion_notification = Bitfield<unsigned char, 1 , 0, 2>;
        using Total_length = Bytefield<unsigned short int, 2>;
        using Identification = Bytefield<unsigned short int, 4>;
        using Flags_reserved_bit = Bitfield<bool, 6, 7, 1>;
        using Flags_donot_fragment = Bitfield<bool, 6,6,1>;
        using Flags_more_fragments = Bitfield<bool, 6,5,1>;
        using Fragment_offset = Bitfield<unsigned short int, 6, 4, 5>;   
        using Time_to_live = Bytefield<unsigned char, 8>;
        using Protocol = Bytefield<unsigned char, 9>;
        using Checksum = Bytefield<unsigned short int, 10>;
        using Source = Bytefield<net::ipv4::address::Custom, 12>;
        using Target = Bytefield<net::ipv4::address::Custom, 16>;

        public:

            Header(unsigned char * data) : 
            version(data+position),
            header_length(data+position),
            differentiated_services_codepoint(data+position),
            explicit_congestion_notification(data+position),
            total_length(data+position),
            identification(data+position),
            reserved_bit(data+position),
            donot_fragment(data+position),
            more_fragments(data+position),
            fragment_offset(data+position),
            ttl(data+position),
            protocol(data+position),
            checksum(data+position),
            source(data+position),
            target(data+position)
            {}

            ~Header(){}

            Version version;
            Header_length header_length;
            Differentiated_services_codepoint differentiated_services_codepoint;
            Explicit_congestion_notification explicit_congestion_notification;
            Total_length total_length;
            Identification identification;
            Flags_reserved_bit reserved_bit;
            Flags_donot_fragment donot_fragment;
            Flags_more_fragments more_fragments;
            Fragment_offset fragment_offset;
            Time_to_live ttl;
            Protocol protocol;
            Checksum checksum;
            Source source;
            Target target;

            static constexpr auto position = 14;
            static constexpr auto size = 20;
    };

}


#endif