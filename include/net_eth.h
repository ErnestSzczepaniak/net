#ifndef _net_eth_h
#define _net_eth_h

/**
 * @file	net_eth.h
 * @author	en2
 * @date	19-10-2020
 * @brief	
 * @details	
**/

#include "net_bitfield.h"
#include "net_bytefield.h"

namespace net::eth
{

namespace address
{

class Custom
{
public:
    Custom() {}
    Custom(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4, unsigned char b5)
    {
        value[0] = b0;
        value[1] = b1;
        value[2] = b2;
        value[3] = b3;
        value[4] = b4;
        value[5] = b5;
    }
    ~Custom() {}

    void operator=(const Custom & other)
    {
        memcpy(value, other.value, 6);
    }

    unsigned char value[6];

}; /* class: Address */


static Custom Broadcast = Custom(0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
static Custom Empty = Custom(0, 0, 0, 0, 0, 0);
static Custom Babe = Custom(0x4b, 0x1d, 0xde, 0xad, 0xba, 0xbe);

}; /* namespace: address */

namespace type
{

static constexpr unsigned short int Aoe = 0x88a2;

}; /* namespace: type */

/* ---------------------------------------------| header |--------------------------------------------- */

class Header
{
    using Address_destination = Bytefield<address::Custom, 0, false>;
    using Address_source = Bytefield<address::Custom, 6, false>;
    using Type = Bytefield<unsigned short int, 12>;

public:
    Header(unsigned char * data) : destination(data), source(data), type(data) {}
    ~Header() {}
  
    Address_destination destination;
    Address_source source;
    Type type;

    static constexpr auto position = 0;
    static constexpr auto size = 14;
}; /* class: Type */

}; /* namespace: net::eth */


#endif /* define: net_eth_h */