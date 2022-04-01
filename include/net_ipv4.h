#ifndef net_ipv4_h
#define net_ipv4_h

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
                memcpy(value, other.value, 4);
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
 
    };
    class Header
    {

        using Version = Bitfield<unsigned char, 0, 4, 4>;
        using Header_length = Bitfield<unsigned char, 0, 0, 4>;
        public:

            Header(unsigned char * data) : version(data+position), header_length(data+position){}
            ~Header(){}

            Version version;
            Header_length header_length;
            static constexpr auto position = 14;
            static constexpr auto size = 20;
    };

}


#endif