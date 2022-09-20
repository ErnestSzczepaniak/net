#ifndef _net_acl_type_h
#define _net_acl_type_h

/**
 * @file	net_acl_type.h
 * @author	en2
 * @date	20-09-2022
 * @brief	
 * @details	
**/

#include "net_ip.h"

namespace net::acl
{

enum class Condition : unsigned char
{
    PERMIT = 0,
    DENY,
    UNKNOWN
}; /* enum: Condition */

enum class Protocol : unsigned char
{
    AHP = 0,
    ESP,
    EIGRP,
    GRE,
    ICMP,
    IGMP,
    IGRP,
    IP,
    IPINIP,
    NOS,
    OSPF,
    PIM,
    PCP,
    TCP,
    UDP,
    UNKNOWN
}; /* enum: Protocol */

enum class Schema_address : unsigned char
{
    VALUE = 0,
    ANY,
    HOST,
    UNKNOWN
}; /* enum: Schema */

enum class Schema_wildcard : unsigned char
{
    VALUE = 0,
    ANY,
    HOST,
    UNKNOWN
}; /* enum: Schema_wildcard */

enum class Schema_port : unsigned char
{
    LESS_THAN = 0,
    GRATE_THAN,
    EQUAL,
    NOT_EQUAL,
    RANGE,
    UNKNOWN
}; /* enum: Schema_port */

struct Policy
{
    int sequence_number = -1;
    Condition condition = Condition::UNKNOWN;
    Protocol protocol = Protocol::UNKNOWN;
    bool log = false;

    Schema_address source_address_schema = Schema_address::UNKNOWN;
    net::ip::address::Custom source_address;
    Schema_wildcard source_wildcard_schema = Schema_wildcard::UNKNOWN;
    net::ip::wildcard::Custom source_wildcard;

    Schema_port source_port_schema = Schema_port::UNKNOWN;
    unsigned short source_port_0 = -1;
    unsigned short source_port_1 = -1;

    Schema_address destination_address_schema = Schema_address::UNKNOWN;
    net::ip::address::Custom destination_address;
    Schema_wildcard destination_wildcard_schema = Schema_wildcard::UNKNOWN;
    net::ip::wildcard::Custom destination_wildcard;

    Schema_port destination_port_schema = Schema_port::UNKNOWN;
    unsigned short destination_port_0 = -1;
    unsigned short destination_port_1 = -1;
}; /* structure: Policy */

}; /* namespace: net::acl */

#endif /* define: net_acl_type_h */