#ifndef _net_ip_type_h
#define _net_ip_type_h

/**
 * @file	net_ip_type.h
 * @author	en2
 * @date	15-09-2022
 * @brief	
 * @details	
**/

namespace net::ip
{

enum class Protocol : unsigned char
{
    ICMP = 0x01,
    TCP = 0x06,
    UDP = 0x11
}; /* enum: Protocol */

enum class Ecn : unsigned char
{
    NON_ECN_CAPABLE_TRANSPORT = 0x00,
    ECN_CAPABLE_0_TRANSPORT = 0x01,
    ECN_CAPABLE_1_TRANSPORT = 0x02,
    CONGESTION_ENCOUNTERED_TRANSPORT = 0x03
}; /* enum: Ecn */

}; /* namespace: net::ip */

#endif /* define: net_ip_type_h */