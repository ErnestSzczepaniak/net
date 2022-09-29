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

bool Instance::add(char * record)
{
    auto policy = _parser.parse(record);

    for (int i = 0; i < _count; i++)
    {
        if (_policy[i].sequence_number == policy.sequence_number) return false;
        if (_policy[i].sequence_number < policy.sequence_number) continue;

        for (int j = 0; j < _count - i; j++) _policy[_count - j] = _policy[_count - j - 1];

        _policy[i] = policy;
        _count++;

        return true;
    }

    _policy[_count++]  = policy;

    return true;
}

bool Instance::remove(int sequence_number)
{
    for (int i = 0; i < _count; i++)
    {
        if (_policy[i].sequence_number != sequence_number) continue;

        for (int j = 0; j < _count - i; j++) _policy[i + j] = _policy[i + j + 1];

        _count--;

        return true;
    }

    return false;
}

Instance::Result_check Instance::check(unsigned char * buffer)
{
    auto header_eth = net::eth::Header(buffer);
    auto header_ip = net::ip::Header(header_eth.payload);

    for (int i = 0; i < _count; i++)
    {


    }
    
    return {};
}

}; /* namespace: net::spd */
