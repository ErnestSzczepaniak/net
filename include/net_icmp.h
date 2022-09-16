#ifndef _net_icmp_h
#define _net_icmp_h

/**
 * @file	net_icmp.h
 * @author	en2
 * @date	16-09-2022
 * @brief	
 * @details	
**/

#include "net_generic_bytes.h"

namespace net::icmp
{

/* ---------------------------------------------| type |--------------------------------------------- */

enum class Type : unsigned char
{
    ECHO_REPLY = 0x00,
    DESTINATION_UNREACHABLE = 0x03,
    SOURCE_QUENCH = 0x04,
    REDIRECT_MESSAGE = 0x05,
    ECHO_REQUEST = 0x08,
    ROUTER_ADVERTISEMENT = 0x09,
    ROUTER_SOLICITATION = 0x0A,
    TIME_EXCEEDED = 0x0B,
    PARAMETER_PROBLEM = 0x0C,
    TIMESTAMP = 0x0D,
    TIMESTAMP_REPLY = 0x0E,
    INFORMATION_REQUEST = 0x0F,
    INFORMATION_REPLY = 0x10,
    ADDRESS_MASK_REQUEST = 0x11,
    ADDRESS_MASK_REPLY = 0x12,
    TRACEROUTE = 0x1E,
    EXTENDED_ECHO_REQUEST = 0x2a,
    EXTENDED_ECHO_REPLY = 0x2b

}; /* enum: Type */

enum class Code_destination_unreachable : unsigned char
{
    NETWORK_UNREACHABLE = 0x00,
    HOST_UNREACHABLE = 0x01,
    PROTOCOL_UNREACHABLE = 0x02,
    PORT_UNREACHABLE = 0x03,
    FRAGMENTATION_NEEDED_AND_DF_SET = 0x04,
    SOURCE_ROUTE_FAILED = 0x05,
    DESTINATION_NETWORK_UNKNOWN = 0x06,
    DESTINATION_HOST_UNKNOWN = 0x07,
    SOURCE_HOST_ISOLATED = 0x08,
    NETWORK_ADMINISTRATIVELY_PROHIBITED = 0x09,
    HOST_ADMINISTRATIVELY_PROHIBITED = 0x0A,
    NETWORK_UNREACHABLE_FOR_TOS = 0x0B,
    HOST_UNREACHABLE_FOR_TOS = 0x0C,
    COMMUNICATION_ADMINISTRATIVELY_PROHIBITED = 0x0D,
    HOST_PRECEDENCE_VIOLATION = 0x0E,
    PRECEDENCE_CUTOFF_IN_EFFECT = 0x0F
}; /* enum: Code_destination_unreachable */

/* ---------------------------------------------| header |--------------------------------------------- */

class Header
{
public:
    Header(unsigned char * buffer);
    ~Header();

    generic::Bytes<Type, 0, false> type;
    generic::Bytes<unsigned char, 1, false> code;
    generic::Bytes<unsigned short int, 2, true> checksum;

}; /* class: Header */

/* ---------------------------------------------| Echo windows |--------------------------------------------- */

class Echo_request_windows : public Header
{
    static constexpr auto size = 8;

public:
    Echo_request_windows(unsigned char * buffer);
    ~Echo_request_windows();

    generic::Bytes<unsigned short int, 4, true> identifier;
    generic::Bytes<unsigned short int, 6, true> sequence_number;

    unsigned char * payload;

}; /* class: Echo_request */

using Echo_response_windows = Echo_request_windows;

/* ---------------------------------------------| Echo linux |--------------------------------------------- */

class Echo_request_linux : public Header
{
    static constexpr auto size = 16;

public:
    Echo_request_linux(unsigned char * buffer);
    ~Echo_request_linux();

    generic::Bytes<unsigned short int, 4, true> identifier;
    generic::Bytes<unsigned short int, 6, true> sequence_number;
    generic::Bytes<unsigned int, 8, true> originate_timestamp;
    generic::Bytes<unsigned int, 12, true> receive_timestamp;

    unsigned char * payload;

}; /* class: Echo_request */

using Echo_response_linux = Echo_request_linux;

}; /* namespace: net::icmp */

#endif /* define: net_icmp_h */