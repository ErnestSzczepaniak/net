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

class Header : public generic::Header
{
    static constexpr auto size = 14;

    using Address_destination = generic::Bytes<address::Custom, 0, false>;
    using Address_source = generic::Bytes<address::Custom, 6, false>;
    using Type = generic::Bytes<unsigned short int, 12, true>;

public:
    Header(unsigned char * buffer);
    ~Header();

    Address_destination address_destination;
    Address_source address_source;
    Type type;

}; /* class: Header */

}; /* namespace: net::eth */

#endif /* define: net_eth_header_h */