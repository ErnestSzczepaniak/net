#include "net_icmp_code.h"

namespace net::icmp::stack
{
    const char * parse(Code value)
    {
        if (value == Code::HEADER_ETH_ADDRESS_DESTINATION) return "Header ETH Address Destination";
        else if (value == Code::HEADER_ETH_ADDRESS_SOURCE) return "Header ETH Address Source";
        else if (value == Code::HEADER_ETH_TYPE) return "Header ETH Type";
        else if (value == Code::IO_TX) return "IO TX";
        else if (value == Code::IO_RX) return "IO RX";
        else if (value == Code::IO_TIMEOUT) return "IO TIMEOUT";
        else if (value == Code::IO_SIZE) return "IO SIZE";
        else if (value == Code::SUCCESS) return "SUCCESS";
    }
}