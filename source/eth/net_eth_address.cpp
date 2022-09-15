#include "net_eth_address.h"
#include <cstdlib>
#include <cstring>

namespace net::eth::address
{

Custom::Custom()
{

}

Custom::Custom(const char * value)
{
    if (strlen(value) != 17) return;

    for (int i = 0; i < 6; i++)
    {
        _data[i] = _withdraw(value, i);
    }
}

Custom::~Custom()
{

}
bool Custom::operator==(const Custom & other)
{
    return (memcmp(_data, other._data, 6) == 0);
}

unsigned char Custom::_withdraw(const char * value, int index)
{
    char * pointer = nullptr;

    if (index == 0) pointer = (char * ) value;
    else
    {
        auto counter = 0;

        for (int i = 0; i < strlen(value); i++)
        {
            if (value[i] == ':') counter++;
            if (counter == index)
            {
                pointer = (char * ) &value[i + 1];
                break;
            }
        }
    }

    return (unsigned char) strtol(pointer, nullptr, 16);
}

}; /* namespace:  */