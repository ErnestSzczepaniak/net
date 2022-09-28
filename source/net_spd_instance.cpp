#include "net_spd_instance.h"
#include "net.h"

namespace net::spd
{

Instance::Instance()
{

}

Instance::~Instance()
{

}

bool Instance::add(char * policy)
{
    memcpy(_policy[_count++], policy, strlen(policy));

    return true;
}

bool Instance::remove(int priority)
{
    return true;
}

bool Instance::check(unsigned char * buffer)
{
    auto header_eth = net::eth::Header(buffer);
    auto header_ip = net::ip::Header(header_eth.payload);

    for (int i = 0; i < _count; i++)
    {
        auto policy = _parse.policy(_policy[i]);

        if (auto result = _verify_protocol(header_ip, policy.protocol); result == false) continue;




        return policy.condition == Condition::PERMIT;
    }
    
    return false;
}

/* ---------------------------------------------| private |--------------------------------------------- */

bool Instance::_verify_protocol(ip::Header & header, Protocol protocol)
{
    if (protocol == Protocol::IP && header.protocol == ip::Protocol::TCP) return true;
    else if (protocol == Protocol::IP && header.protocol == ip::Protocol::UDP) return true;
    else if (protocol == Protocol::IP && header.protocol == ip::Protocol::ICMP) return true;
    else if (protocol == Protocol::TCP && header.protocol == ip::Protocol::TCP) return true;
    else if (protocol == Protocol::UDP && header.protocol == ip::Protocol::UDP) return true;
    else if (protocol == Protocol::ICMP && header.protocol == ip::Protocol::ICMP) return true;

    return false;
}

}; /* namespace: net::spd */
