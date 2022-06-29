#ifndef NET_ARP_CODE_H
#define NET_ARP_CODE_H

namespace net::arp::stack
{
    enum class Code : unsigned char
    {
        SUCCESS,

        HEADER_ETH_ADDRESS_DESTINATION,
        HEADER_ETH_ADDRESS_SOURCE,
        HEADER_ETH_TYPE,

        HEADER_ARP_HARDWARE_TYPE,
        HEADER_ARP_PROTOCOL_TYPE,
        HEADER_ARP_HARDWARE_SIZE,
        HEADER_ARP_PROTOCOL_SIZE,
        HEADER_ARP_OPCODE,
        HEADER_ARP_SENDER_MAC,
        HEADER_ARP_SENDER_IP,
        HEADER_ARP_TARGET_MAC,
        HEADER_ARP_TARGET_IP,

        IO_TX,
        IO_RX,
        IO_TIMEOUT,
        IO_SIZE

    }; /* enum: Result */

    const char * parse(Code value);

};

#endif