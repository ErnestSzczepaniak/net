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

class Custom
{
public:
    Custom();
    Custom(const char * value);
    ~Custom();


}; /* class: Custom */

static Custom ipv4 = Custom("ipv4");
static Custom ipv6 = Custom("ipv6");

}; /* namespace: net::eth::type */

#endif /* define: net_eth_type_h */