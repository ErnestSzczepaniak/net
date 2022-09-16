#include "net_arp.h"

namespace net::arp
{

Header::Header(unsigned char * buffer) :
hardware_type(buffer),
protocol_type(buffer),
hardware_size(buffer),
protocol_size(buffer),
operation(buffer),
sender_mac_address(buffer),
sender_ip_address(buffer),
target_mac_address(buffer),
target_ip_address(buffer)
{

}

Header::~Header()
{

}


}; /* namespace: net::arp */
