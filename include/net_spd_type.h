#ifndef _net_spd_type_h
#define _net_spd_type_h

/**
 * @file	net_spd_type.h
 * @author	en2
 * @date	28-09-2022
 * @brief	
 * @details	
**/

#include "net_ip.h"

namespace net::spd
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

enum class Precedence : unsigned char
{
    MATCH = 0,
    PRIORITY,
    IMMEDIATE,
    FLASH,
    FLASH_OVERRIDE,
    CRITICAL,
    INTERNET,
    NETWORK,
    UNKNOWN
}; /* enum: Precedence */

enum class Dscp : unsigned char
{
    DEFAULT = 0b000000,
    AF11 = 0b001010,
    AF12 = 0b001100,
    AF13 = 0b001110,
    AF21 = 0b010010,
    AF22 = 0b010100,
    AF23 = 0b010110,
    AF31 = 0b011010,
    AF32 = 0b011100,
    AF33 = 0b011110,
    AF41 = 0b100010,
    AF42 = 0b100100,
    AF43 = 0b100110,
    CS1 = 0b001000,
    CS2 = 0b010000,
    CS3 = 0b011000,
    CS4 = 0b100000,
    CS5 = 0b101000,
    CS6 = 0b110000,
    CS7 = 0b111000,
    EF = 0b101110,
    UNKNOWN
}; /* enum: Dscp */

enum class Port_operation : unsigned char
{
    LESS_THAN = 0,
    GREATER_THAN,
    EQUAL,
    NOT_EQUAL,
    RANGE,
    UNKNOWN
}; /* enum: Port_operator */

struct Group_port
{
    Port_operation operation;
    unsigned short value0;
    unsigned short value1;
}; /* struct: Group_port */

struct Group_address
{
    net::ip::address::Custom address;
    net::ip::address::Custom wildcard;
}; /* structure: Group_address */

struct Direction
{
    net::ip::address::Custom address;
    net::ip::address::Custom wildcard;
    Group_port port;
}; /* structure: Direction */

struct Policy
{
    int sequence_number = -1;
    Condition condition = Condition::UNKNOWN;
    Protocol protocol = Protocol::UNKNOWN;
    Direction source;
    Direction destination;
    Precedence precedence = Precedence::UNKNOWN;
    Dscp dscp = Dscp::UNKNOWN;
    bool log = false;
}; /* structure: Policy */

}; /* namespace: net::spd */

#endif /* define: net_spd_type_h */