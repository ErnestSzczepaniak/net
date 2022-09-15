#include "net_eth_header.h"

namespace net::eth
{

Header::Header(unsigned char * buffer) : 
address_destination(buffer),
address_source(buffer),
type(buffer)
{
    payload = buffer + size;
}

Header::~Header()
{

}

}; /* namespace: net::eth */
