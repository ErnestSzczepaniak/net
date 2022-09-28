#ifndef _net_spd_instance_h
#define _net_spd_instance_h

/**
 * @file	net_spd_instance.h
 * @author	en2
 * @date	28-09-2022
 * @brief	
 * @details	
**/

#include "net_spd_parse.h"
#include "net_tcp.h"
#include "net_udp.h"

namespace net::spd
{

class Instance
{
    static constexpr auto size_policy =     256;
    static constexpr auto number_policy =   256;

public:
    Instance();
    ~Instance();

    bool add(char * policy);
    bool remove(int priority);

    bool check(unsigned char * buffer);

protected:
    bool _verify_protocol(ip::Header & header, Protocol protocol);

private:
    char _policy[number_policy][size_policy];
    int _count = 0;

    Parse _parse;

}; /* class: Instance */

}; /* namespace: net::spd */

#endif /* define: net_spd_instance_h */