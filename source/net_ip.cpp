#include "net_ip.h"

namespace net::ip
{

Header::Header(unsigned char * buffer) :
version(buffer),
header_length(buffer),
dscp(buffer),
ecn(buffer),
total_length(buffer),
identification(buffer),
dont_fragment(buffer),
more_fragments(buffer),
fragment_offset(buffer),
time_to_live(buffer),
protocol(buffer),
header_checksum(buffer),
address_source(buffer),
address_destination(buffer)
{
    payload = buffer + header_length.operator unsigned char() * 4;
}

Header::~Header()
{

}

}; /* namespace: net::ip */
