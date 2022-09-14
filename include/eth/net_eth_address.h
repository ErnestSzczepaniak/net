#ifndef _net_eth_address_h
#define _net_eth_address_h

/**
 * @file	net_eth_address.h
 * @author	en2
 * @date	13-09-2022
 * @brief	
 * @details	
**/

namespace net::eth::address
{

class Custom
{
public:
    Custom();
    Custom(const char * value);
    ~Custom();

    bool operator==(const char * value);
    bool operator==(const Custom & value);

protected:
    unsigned char _withdraw(const char * value, int index);

private:
    unsigned char _address[6];

}; /* class: Address */

static Custom Broadcast = Custom("ff:ff:ff:ff:ff:ff");
static Custom Empty = Custom("00:00:00:00:00:00");

}; /* namespace: net::eth::address */

#endif /* define: net_eth_address_h */