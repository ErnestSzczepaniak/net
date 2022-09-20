#ifndef _net_eth_h
#define _net_eth_h

/**
 * @file	net_eth.h
 * @author	en2
 * @date	14-09-2022
 * @brief	
 * @details	
**/

#include "net_generic_bytes.h"
#include "net_generic_stream.h"

namespace net::eth
{

/* ---------------------------------------------| address |--------------------------------------------- */

namespace address
{

using Custom = generic::Stream<6, 0x3a, 16, false>;

}; /* namespace: net::eth::address */

/* ---------------------------------------------| type |--------------------------------------------- */

enum class Type : unsigned short int
{
    IPv4 =  0x0800,
    IPv6 =  0x86DD,
    ARP =   0x0806,
    AoE =   0x88a2
}; /* enum: Type */

/* ---------------------------------------------| header |--------------------------------------------- */

class Header
{
    static constexpr auto size = 14;

public:
    Header(unsigned char * buffer);
    ~Header();

    generic::Bytes<address::Custom, 0, false> address_destination;
    generic::Bytes<address::Custom, 6, false> address_source;
    generic::Bytes<Type, 12, true> type;

    unsigned char * payload;

}; /* class: Header */


}; /* namespace: net::eth */

#endif /* define: net_eth_h */