#ifndef _net_eth_type_h
#define _net_eth_type_h

/**
 * @file	net_eth_type.h
 * @author	en2
 * @date	13-09-2022
 * @brief	
 * @details	
**/

namespace net::eth
{

enum class Type : unsigned short int
{
    IPv4 = 0x0800,
    IPv6 = 0x86DD,
    ARP = 0x0806,
    AoE = 0x88a2
}; /* enum: Type */

}; /* namespace: net::eth::type */

#endif /* define: net_eth_type_h */