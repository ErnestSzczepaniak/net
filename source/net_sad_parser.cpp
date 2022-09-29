#include "net_sad_parser.h"

namespace net::sad
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

    result.traffic = _traffic(policy);

    auto source = _group_direction(policy, 1);
    result.source = source;

    auto destination = _group_direction(policy, 3);
    result.destination = destination;

    result.spi = _spi(policy);
    result.sequence_number = _sequence_number(policy);
    result.ttl_seconds = _ttl_seconds(policy);
    result.ttl_bytes = _ttl_bytes(policy);

    return result;
}

Traffic Parser::_traffic(char * policy)
{
    if (_word_matches(policy, 0, "outbound")) return Traffic::OUTBOUND;
    else if (_word_matches(policy, 0, "inbound")) return Traffic::INBOUND;

    return Traffic::UNKNOWN;
}

Group_direction Parser::_group_direction(char * policy, int index)
{
    Group_direction result;

    result.tunnel.address = _word_cast<ip::address::Custom>(policy, index);
    result.local.address = _word_cast<ip::address::Custom>(policy, index + 1);

    return result;
}

unsigned long long int Parser::_spi(char * policy)
{
    return _word_cast<unsigned long long int>(policy, 5);
}

unsigned long long int Parser::_sequence_number(char * policy)
{
    return _word_cast<unsigned long long int>(policy, 6);
}

unsigned int Parser::_ttl_seconds(char * policy)
{
    return _word_cast<int>(policy, 7);
}

unsigned int Parser::_ttl_bytes(char * policy)
{
    return _word_cast<int>(policy, 8);
}

}; /* namespace: net::sad */
