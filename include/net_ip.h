#ifndef _net_ip_h
#define _net_ip_h

/**
 * @file	net_ip.h
 * @author	en2
 * @date	14-09-2022
 * @brief	
 * @details	
**/

#include "net_generic_bytes.h"
#include "net_generic_bits.h"
#include "net_generic_stream.h"

namespace net::ip
{

/* ---------------------------------------------| address |--------------------------------------------- */

namespace address
{

using Custom = generic::Stream<4, 0x2e, 10, false>;

}; /* namespace: address */

/* ---------------------------------------------| netmask |--------------------------------------------- */

namespace netmask
{

using Custom = generic::Stream<4, 0x2e, 10, false>;

}; /* namespace: netmask */

/* ---------------------------------------------| wildcard |--------------------------------------------- */

namespace wildcard
{

using Custom = generic::Stream<4, 0x2e, 10, true>;

}; /* namespace: wildcard */

/* ---------------------------------------------| type |--------------------------------------------- */

enum class Protocol : unsigned char
{
    ICMP = 0x01,
    TCP = 0x06,
    UDP = 0x11,
    ESP = 0x32
}; /* enum: Protocol */

enum class Ecn : unsigned char
{
    NON_ECN_CAPABLE_TRANSPORT = 0x00,
    ECN_CAPABLE_0_TRANSPORT = 0x01,
    ECN_CAPABLE_1_TRANSPORT = 0x02,
    CONGESTION_ENCOUNTERED_TRANSPORT = 0x03
}; /* enum: Ecn */

/* ---------------------------------------------| header |--------------------------------------------- */

class Header
{
public:
    Header(unsigned char * buffer);
    ~Header();

    generic::Bits<unsigned char, 0, 4, 4> version;
    generic::Bits<unsigned char, 0, 0, 4> header_length;
    generic::Bits<unsigned char, 1, 2, 6> dscp;
    generic::Bits<Ecn, 1, 0, 2> ecn;
    generic::Bytes<unsigned short int, 2, true> total_length;
    generic::Bytes<unsigned short int, 4, true> identification;
    generic::Bits<bool, 6, 5, 1> more_fragments;
    generic::Bits<bool, 6, 6, 1> dont_fragment;
    generic::Bits<unsigned short int, 7, 0, 13> fragment_offset;
    generic::Bytes<unsigned char, 8, false> time_to_live;
    generic::Bytes<Protocol, 9, false> protocol;
    generic::Bytes<unsigned short int, 10, true> header_checksum;
    generic::Bytes<address::Custom, 12, false> address_source;
    generic::Bytes<address::Custom, 16, false> address_destination;

    unsigned char * payload;

}; /* class: Header */

}; /* namespace: net::ip */

#endif /* define: net_ip_h */