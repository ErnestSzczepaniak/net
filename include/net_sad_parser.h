#ifndef _net_sad_parser_h
#define _net_sad_parser_h

/**
 * @file	net_sad_parser.h
 * @author	en2
 * @date	29-09-2022
 * @brief	
 * @details	
**/

#include "net_generic_parser.h"
#include "net_sad_type.h"

namespace net::sad
{

class Parser : public generic::Parser
{
public:
    Parser();
    ~Parser();

    Policy parse(char * policy);

protected:
    Traffic _traffic(char * policy);
    Group_direction _group_direction(char * policy, int index);
    unsigned long long int _spi(char * policy);
    unsigned long long int _sequence_number(char * policy);
    unsigned int _ttl_seconds(char * policy);
    unsigned int _ttl_bytes(char * policy);

}; /* class: Parser */

}; /* namespace: net::sad */

#endif /* define: net_sad_parser_h */