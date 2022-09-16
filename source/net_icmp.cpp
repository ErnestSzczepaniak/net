#include "net_icmp.h"

namespace net::icmp
{

/* ---------------------------------------------| header |--------------------------------------------- */

Header::Header(unsigned char * buffer) :
type(buffer),
code(buffer),
checksum(buffer)
{

}

Header::~Header()
{

}

/* ---------------------------------------------| echo windows |--------------------------------------------- */

Echo_request_windows::Echo_request_windows(unsigned char * buffer) : 
Header(buffer),
identifier(buffer),
sequence_number(buffer)
{
    payload = buffer + size;
}

Echo_request_windows::~Echo_request_windows()
{

}

/* ---------------------------------------------| echo linux |--------------------------------------------- */

Echo_request_linux::Echo_request_linux(unsigned char * buffer) : 
Header(buffer),
identifier(buffer),
sequence_number(buffer),
originate_timestamp(buffer),
receive_timestamp(buffer)
{
    payload = buffer + size;
}

Echo_request_linux::~Echo_request_linux()
{

}

}; /* namespace: net::icmp */
