#include "net_udp.h"

namespace net::udp
{

Header::Header(unsigned char * buffer) :
source_port(buffer),
destination_port(buffer),
length(buffer),
checksum(buffer)
{
    payload = buffer + size;
}

Header::~Header()
{

}

}; /* namespace: net::udp */
