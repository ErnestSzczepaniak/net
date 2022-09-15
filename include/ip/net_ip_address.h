#ifndef _net_ip_address_h
#define _net_ip_address_h

/**
 * @file	net_ip_address.h
 * @author	en2
 * @date	14-09-2022
 * @brief	
 * @details	
**/

namespace net::ip::address
{

class Custom
{
public:
    Custom();
    Custom(const char * value);
    ~Custom();

    bool operator==(const Custom & other);

protected:
    unsigned char _withdraw(const char * value, int index);

private:
    unsigned char _data[4];

}; /* class: Custom */

}; /* namespace: net::ip::address */

#endif /* define: net_ip_address_h */