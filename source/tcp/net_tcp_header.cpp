#include "net_tcp_header.h"

namespace net::tcp
{

Header::Header(unsigned char * buffer) :
source_port(buffer),
destination_port(buffer),
sequence_number(buffer),
acknowledgment_number(buffer),
header_length(buffer),
reserved(buffer),
ns(buffer),
cwr(buffer),
ece(buffer),
urg(buffer),
ack(buffer),
psh(buffer),
rst(buffer),
syn(buffer),
fin(buffer),
window_size(buffer),
checksum(buffer),
urgent_pointer(buffer)
{
    payload = buffer + header_length.operator unsigned char() * 4;
}

Header::~Header()
{

}

}; /* namespace: net::tcp */
