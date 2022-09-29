#include "net_spd_parser.h"

namespace net::spd
{

Parser::Parser()
{

}

Parser::~Parser()
{

}

Policy Parser::parse(char * policy)
{
    Policy result;

    result.sequence_number = _sequence_number(policy);
    result.condition = _condition(policy);
    result.protocol = _protocol(policy);

    auto [address_source, port_source_index] = _group_address(policy, 3);
    result.source.address = address_source.address;
    result.source.wildcard = address_source.wildcard;

    auto [port_source, address_destination_index] = _group_port(policy, port_source_index);
    result.source.port.operation = port_source.operation;
    result.source.port.value0 = port_source.value0;
    result.source.port.value1 = port_source.value1;

    auto [address_destination, port_destination_index] = _group_address(policy, address_destination_index);
    result.destination.address = address_destination.address;
    result.destination.wildcard = address_destination.wildcard;

    auto [port_destination, log_index] = _group_port(policy, port_destination_index);
    result.destination.port.operation = port_destination.operation;
    result.destination.port.value0 = port_destination.value0;
    result.destination.port.value1 = port_destination.value1;

    result.precedence = _precedence(policy);
    result.dscp = _dscp(policy);
    result.log = _log(policy);

    return result;
}

int Parser::_sequence_number(char * policy)
{
    return _word_cast<int>(policy, 0);
}

Condition Parser::_condition(char * policy)
{
    if (_word_matches(policy, 1, "permit")) return Condition::PERMIT;
    else if (_word_matches(policy, 1, "deny")) return Condition::DENY;

    return Condition::UNKNOWN;
}

Protocol Parser::_protocol(char * policy)
{
    if (_word_matches(policy, 2, "ahp")) return Protocol::AHP;
    else if (_word_matches(policy, 2, "esp")) return Protocol::ESP;
    else if (_word_matches(policy, 2, "eigrp")) return Protocol::EIGRP;
    else if (_word_matches(policy, 2, "gre")) return Protocol::GRE;
    else if (_word_matches(policy, 2, "icmp")) return Protocol::ICMP;
    else if (_word_matches(policy, 2, "igmp")) return Protocol::IGMP;
    else if (_word_matches(policy, 2, "ip")) return Protocol::IP;
    else if (_word_matches(policy, 2, "ipinip")) return Protocol::IPINIP;
    else if (_word_matches(policy, 2, "nos")) return Protocol::NOS;
    else if (_word_matches(policy, 2, "ospf")) return Protocol::OSPF;
    else if (_word_matches(policy, 2, "pim")) return Protocol::PIM;
    else if (_word_matches(policy, 2, "pcp")) return Protocol::PCP;
    else if (_word_matches(policy, 2, "tcp")) return Protocol::TCP;
    else if (_word_matches(policy, 2, "udp")) return Protocol::UDP;

    return Protocol::UNKNOWN;
}

Parser::Result_address Parser::_group_address(char * policy, int index)
{
    Group_address result;

    if (_word_matches(policy, index, "any"))
    {
        result.address = ip::address::Custom("0.0.0.0");
        result.wildcard = ip::address::Custom("255.255.255.255");

        index += 1;
    }
    else if (_word_matches(policy, index, "host"))
    {
        result.address = _word_cast<ip::address::Custom>(policy, index + 1);
        result.wildcard = ip::address::Custom("0.0.0.0");

        index += 2;
    }
    else
    {
        result.address = _word_cast<ip::address::Custom>(policy, index);
        result.wildcard = _word_cast<ip::address::Custom>(policy, index + 1);

        index += 2;
    }

    return {result, index};
}

Parser::Result_port Parser::_group_port(char * policy, int index)
{
    Group_port result;

    if (_word_matches(policy, index, "lt")) result.operation = Port_operation::LESS_THAN;
    else if (_word_matches(policy, index, "gt")) result.operation = Port_operation::GREATER_THAN;
    else if (_word_matches(policy, index, "eq")) result.operation = Port_operation::EQUAL;
    else if (_word_matches(policy, index, "neq")) result.operation = Port_operation::NOT_EQUAL;
    else if (_word_matches(policy, index, "range")) result.operation = Port_operation::RANGE; 

    if (result.operation != Port_operation::RANGE)
    {
        result.value0 = _word_cast<int>(policy, index + 1);

        index += 2;
    }
    else
    {
        result.value0 = _word_cast<int>(policy, index + 1);
        result.value1 = _word_cast<int>(policy, index + 2);

        index += 3;
    }

    return {result, index};
}

Precedence Parser::_precedence(char * policy)
{
    auto present = _word_present(policy, "precedence");

    if (present == false) return Precedence::UNKNOWN;

    auto index = _word_index(policy, "precedence");

    if (_word_matches(policy, index + 1, "match")) return Precedence::MATCH;
    else if (_word_matches(policy, index + 1, "priority")) return Precedence::PRIORITY;
    else if (_word_matches(policy, index + 1, "immediate")) return Precedence::IMMEDIATE;
    else if (_word_matches(policy, index + 1, "flash")) return Precedence::FLASH;
    else if (_word_matches(policy, index + 1, "flash-override")) return Precedence::FLASH_OVERRIDE;
    else if (_word_matches(policy, index + 1, "critical")) return Precedence::CRITICAL;
    else if (_word_matches(policy, index + 1, "internet")) return Precedence::INTERNET;
    else if (_word_matches(policy, index + 1, "network")) return Precedence::NETWORK;

    return Precedence::UNKNOWN;
}

Dscp Parser::_dscp(char * policy)
{
    auto present = _word_present(policy, "dscp");

    if (present == false) return Dscp::UNKNOWN;

    auto index = _word_index(policy, "dscp");

    if (_word_matches(policy, index + 1, "af11")) return Dscp::AF11;
    else if (_word_matches(policy, index + 1, "af12")) return Dscp::AF12;
    else if (_word_matches(policy, index + 1, "af13")) return Dscp::AF13;
    else if (_word_matches(policy, index + 1, "af21")) return Dscp::AF21;
    else if (_word_matches(policy, index + 1, "af22")) return Dscp::AF22;
    else if (_word_matches(policy, index + 1, "af23")) return Dscp::AF23;
    else if (_word_matches(policy, index + 1, "af31")) return Dscp::AF31;
    else if (_word_matches(policy, index + 1, "af32")) return Dscp::AF32;
    else if (_word_matches(policy, index + 1, "af33")) return Dscp::AF33;
    else if (_word_matches(policy, index + 1, "af41")) return Dscp::AF41;
    else if (_word_matches(policy, index + 1, "af42")) return Dscp::AF42;
    else if (_word_matches(policy, index + 1, "af43")) return Dscp::AF43;
    else if (_word_matches(policy, index + 1, "cs1")) return Dscp::CS1;
    else if (_word_matches(policy, index + 1, "cs2")) return Dscp::CS2;
    else if (_word_matches(policy, index + 1, "cs3")) return Dscp::CS3;
    else if (_word_matches(policy, index + 1, "cs4")) return Dscp::CS4;
    else if (_word_matches(policy, index + 1, "cs5")) return Dscp::CS5;
    else if (_word_matches(policy, index + 1, "cs6")) return Dscp::CS6;
    else if (_word_matches(policy, index + 1, "cs7")) return Dscp::CS7;
    else if (_word_matches(policy, index + 1, "ef")) return Dscp::EF;
    else if (_word_matches(policy, index + 1, "default")) return Dscp::DEFAULT;

    return Dscp::UNKNOWN;
}

bool Parser::_log(char * policy)
{
    return _word_present(policy, "log");
}

}; /* namespace: net::spd */
