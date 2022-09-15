#ifndef _net_eth_header_h
#define _net_eth_header_h

/**
 * @file	net_eth_header.h
 * @author	en2
 * @date	14-09-2022
 * @brief	
 * @details	
**/

#include "net_generic.h"
#include "net_eth_address.h"
#include "net_eth_type.h"

namespace net::eth
{

class Header
{
    static constexpr auto size = 14;

public:
    Header(unsigned char * buffer);
    ~Header();

    generic::Bytes<address::Custom, 0, false> address_destination;
    generic::Bytes<address::Custom, 6, false> address_source;
    generic::Bytes<unsigned short int, 12, true> type;

    unsigned char * payload;

}; /* class: Header */

}; /* namespace: net::eth */

#endif /* define: net_eth_header_h */