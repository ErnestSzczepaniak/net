#ifndef _net_sad_type_h
#define _net_sad_type_h

/**
 * @file	net_sad_type.h
 * @author	en2
 * @date	29-09-2022
 * @brief	
 * @details	
**/

#include "net_ip.h"

namespace net::sad
{

enum class Traffic : unsigned char
{
    OUTBOUND = 0,
    INBOUND,
    UNKNOWN
}; /* enum: Traffic */

struct Datapath
{
    ip::address::Custom address;
}; /* structure: Group_address */

struct Group_direction
{
    Datapath tunnel;
    Datapath local;
}; /* structure: Group_direction */

struct Policy
{
    Traffic traffic = Traffic::UNKNOWN;    
    Group_direction source;
    Group_direction destination;
    unsigned long long int spi = 0;
    unsigned long long int sequence_number = 0;
    int ttl_seconds = 0;
    int ttl_bytes = 0;
}; /* structure: Policy */

}; /* namespace: net::sad */

#endif /* define: net_sad_type_h */