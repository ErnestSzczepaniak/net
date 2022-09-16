#ifndef _net_arp_h
#define _net_arp_h

/**
 * @file	net_arp.h
 * @author	en2
 * @date	15-09-2022
 * @brief	
 * @details	
**/

#include "net_generic_bytes.h"
#include "net_eth.h"
#include "net_ip.h"

namespace net::arp
{

/* ---------------------------------------------| type |--------------------------------------------- */

enum class Hardware_type : unsigned short int
{
    ETHERNET = 0x0001
}; /* enum: Hardware_type */

enum class Operation : unsigned short int
{
    REQUEST = 0x0001,
    REPLY = 0x0002,
    REVERSE_REQUEST = 0x0003,
    REVERSE_REPLY = 0x0004
}; /* enum: Operation */

/* ---------------------------------------------| header |--------------------------------------------- */

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

#endif /* define: net_arp_h */