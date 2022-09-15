#ifndef _net_ip_header_h
#define _net_ip_header_h

/**
 * @file	net_ip_header.h
 * @author	en2
 * @date	14-09-2022
 * @brief	
 * @details	
**/

#include "net_generic.h"
#include "net_ip_address.h"
#include "net_ip_type.h"

namespace net::ip
{

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

#endif /* define: net_ip_header_h */