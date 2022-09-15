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

namespace net::ip
{

class Header : public generic::Header
{
    using Version = generic::Bits<unsigned char, 0, 4, 4>;
    using Header_length = generic::Bits<unsigned char, 0, 0, 4>;
    using Precendence = generic::Bits<unsigned char, 1, 5, 3>;
    using Delay = generic::Bits<bool, 1, 4, 1>;
    using Throughput = generic::Bits<bool, 1, 3, 1>;
    using Reliability = generic::Bits<bool, 1, 2, 1>;
    using Total_length = generic::Bytes<unsigned short int, 2, true>;
    using Identification = generic::Bytes<unsigned short int, 4, true>;
    using Dont_fragment = generic::Bits<bool, 6, 6, 1>;
    using More_fragments = generic::Bits<bool, 6, 5, 1>;
    using Fragment_offset = generic::Bits<unsigned short int, 7, 0, 13>;
    using Time_to_live = generic::Bytes<unsigned char, 8, false>;
    using Protocol = generic::Bytes<unsigned char, 9, false>;
    using Header_checksum = generic::Bytes<unsigned short int, 10, true>;
    using Address_source = generic::Bytes<address::Custom, 12, false>;
    using Address_destination = generic::Bytes<address::Custom, 16, false>;
    using Options = generic::Bytes<unsigned char, 20, false>;

public:
    Header(unsigned char * buffer);
    ~Header();

    Version version;
    Header_length header_length;
    Precendence precendence;
    Delay delay;
    Throughput throughput;
    Reliability reliability;
    Total_length total_length;
    Identification identification;
    Dont_fragment dont_fragment;
    More_fragments more_fragments;
    Fragment_offset fragment_offset;
    Time_to_live time_to_live;
    Protocol protocol;
    Header_checksum header_checksum;
    Address_source address_source;
    Address_destination address_destination;

}; /* class: Header */

}; /* namespace: net::ip */

#endif /* define: net_ip_header_h */