#ifndef _net_spd_parser_h
#define _net_spd_parser_h

/**
 * @file	net_spd_parser.h
 * @author	en2
 * @date	28-09-2022
 * @brief	
 * @details	
**/

#include "net_generic_parser.h"
#include "net_spd_type.h"

namespace net::spd
{

class Parser : public generic::Parser
{
    struct Result_address {Group_address address; int next;};
    struct Result_port {Group_port port; int next;};

public:
    Parser();
    ~Parser();

    Policy parse(char * policy);

private:
    int _sequence_number(char * policy);
    Condition _condition(char * policy);
    Protocol _protocol(char * policy);
    Result_address _group_address(char * policy, int index);
    Result_port _group_port(char * policy, int index);
    Precedence _precedence(char * policy);
    Dscp _dscp(char * policy);
    bool _log(char * policy);

}; /* class: Parser */

}; /* namespace: net::spd */

#endif /* define: net_spd_parser_h */