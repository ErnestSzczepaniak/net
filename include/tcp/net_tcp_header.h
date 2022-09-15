#ifndef _net_tcp_header_h
#define _net_tcp_header_h

/**
 * @file	net_tcp_header.h
 * @author	en2
 * @date	15-09-2022
 * @brief	
 * @details	
**/

#include "net_generic.h"
#include "net_tcp_type.h"

namespace net::tcp
{

class Header
{
public:
    Header(unsigned char * buffer);
    ~Header();

    generic::Bytes<unsigned short int, 0, true> source_port;
    generic::Bytes<unsigned short int, 2, true> destination_port;
    generic::Bytes<unsigned int, 4, true> sequence_number;
    generic::Bytes<unsigned int, 8, true> acknowledgment_number;
    generic::Bits<unsigned char, 12, 4, 4> header_length;
    generic::Bits<bool, 12, 1, 3> reserved;
    generic::Bits<bool, 12, 0, 1> ns;
    generic::Bits<bool, 13, 7, 1> cwr;
    generic::Bits<bool, 13, 6, 1> ece;
    generic::Bits<bool, 13, 5, 1> urg;
    generic::Bits<bool, 13, 4, 1> ack;
    generic::Bits<bool, 13, 3, 1> psh;
    generic::Bits<bool, 13, 2, 1> rst;
    generic::Bits<bool, 13, 1, 1> syn;
    generic::Bits<bool, 13, 0, 1> fin;
    generic::Bytes<unsigned short int, 14, true> window_size;
    generic::Bytes<unsigned short int, 16, true> checksum;
    generic::Bytes<unsigned short int, 18, true> urgent_pointer;

    unsigned char * payload;

}; /* class: Header */

}; /* namespace: net::tcp */

#endif /* define: net_tcp_header_h */