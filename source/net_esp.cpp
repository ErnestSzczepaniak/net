#include "net_esp.h"

namespace net::esp
{

Header::Header(unsigned char * buffer) :
spi(buffer),
sequence_number(buffer)
{
    payload = buffer + 8;
}

Header::~Header()
{

}

}; /* namespace: net::esp */
