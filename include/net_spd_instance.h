#ifndef _net_spd_instance_h
#define _net_spd_instance_h

/**
 * @file	net_spd_instance.h
 * @author	en2
 * @date	28-09-2022
 * @brief	
 * @details	
**/

#include "net_spd_parser.h"
#include "net_tcp.h"
#include "net_udp.h"

namespace net::spd
{

class Instance
{
    static constexpr auto size = 256;
    struct Result_check {bool success; Policy policy;};

public:
    Instance();
    ~Instance();

    bool add(char * record);
    bool remove(int sequence_number);

    Result_check check(unsigned char * buffer);

private:
    Policy _policy[size];
    int _count = 0;

    Parser _parser;

}; /* class: Instance */

}; /* namespace: net::spd */

#endif /* define: net_spd_instance_h */