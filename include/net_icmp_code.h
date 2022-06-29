#ifndef NET_ICMP_CODE_H
#define NET_ICMP_CODE_H

namespace net::icmp::stack
{
    enum class Code : unsigned char
    {
        SUCCESS,

        HEADER_ETH_ADDRESS_DESTINATION,
        HEADER_ETH_ADDRESS_SOURCE,
        HEADER_ETH_TYPE,

        HEADER_IPv4_VERSION,
        HEADER_IPv4_HEADER_LENGTH,
        HEADER_IPv4_DSF,
        HEADER_IPv4_TOTAL_LENGTH,
        HEADER_IPv4_IDENTIFICATION,
        HEADER_IPv4_FLAGS,
        HEADER_IPv4_FRAGMENT_OFFSET,
        HEADER_IPv4_TTL,
        HEADER_IPv4_PROTOCOL,
        HEADER_IPv4_CHECKSUM,
        HEADER_IPv4_ADDRESS_SOURCE,
        HEADER_IPv4_ADDRESS_DESTINATION,

        IO_TX,
        IO_RX,
        IO_TIMEOUT,
        IO_SIZE

    }; /* enum: Result */

    const char * parse(Code value);

};

#endif