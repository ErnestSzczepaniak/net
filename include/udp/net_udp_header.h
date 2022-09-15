#ifndef _net_udp_header_h
#define _net_udp_header_h

/**
 * @file	net_udp_header.h
 * @author	en2
 * @date	15-09-2022
 * @brief	
 * @details	
**/

#include "net_generic.h"

namespace net::udp
{

class Header
{
    static constexpr auto size = 8;

public:
    Header(unsigned char * buffer);
    ~Header();

    generic::Bytes<unsigned short int, 0, true> source_port;
    generic::Bytes<unsigned short int, 2, true> destination_port;
    generic::Bytes<unsigned short int, 4, true> length;
    generic::Bytes<unsigned short int, 6, true> checksum;

    unsigned char * payload;

}; /* class: Header */

}; /* namespace: net::udp */

#endif /* define: net_udp_header_h */