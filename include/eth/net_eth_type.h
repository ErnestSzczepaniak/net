#ifndef _net_eth_type_h
#define _net_eth_type_h

/**
 * @file	net_eth_type.h
 * @author	en2
 * @date	13-09-2022
 * @brief	
 * @details	
**/

namespace net::eth::type
{

static constexpr unsigned short int IPv4 =      0x0800;
static constexpr unsigned short int IPv6 =      0x86DD;
static constexpr unsigned short int ARP =       0x0806;
static constexpr unsigned short int AoE =       0x88a2;

}; /* namespace: net::eth::type */

#endif /* define: net_eth_type_h */