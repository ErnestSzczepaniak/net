#ifndef _net_arp_type_h
#define _net_arp_type_h

/**
 * @file	net_arp_type.h
 * @author	en2
 * @date	15-09-2022
 * @brief	
 * @details	
**/

namespace net::arp
{

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

}; /* namespace: net::arp */

#endif /* define: net_arp_type_h */