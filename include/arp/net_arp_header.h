#ifndef _net_arp_header_h
#define _net_arp_header_h

/**
 * @file	net_arp_header.h
 * @author	en2
 * @date	15-09-2022
 * @brief	
 * @details	
**/

#include "net_generic.h"
#include "net_eth.h"
#include "net_ip.h"
#include "net_arp_type.h"

namespace net::arp
{

class Header
{
public:
    Header(unsigned char * buffer);
    ~Header();

    generic::Bytes<Hardware_type, 0, true> hardware_type;
    generic::Bytes<eth::Type, 2, true> protocol_type;
    generic::Bytes<unsigned char, 4, false> hardware_size;
    generic::Bytes<unsigned char, 5, false> protocol_size;
    generic::Bytes<Operation, 6, true> operation;
    generic::Bytes<eth::address::Custom, 8, false> sender_mac_address;
    generic::Bytes<ip::address::Custom, 14, false> sender_ip_address;
    generic::Bytes<eth::address::Custom, 18, false> target_mac_address;
    generic::Bytes<ip::address::Custom, 24, false> target_ip_address;

}; /* class: Header */

}; /* namespace: net::arp */

#endif /* define: net_arp_header_h */