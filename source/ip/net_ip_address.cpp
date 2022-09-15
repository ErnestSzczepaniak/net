#include "net_ip_address.h"
#include <cstdlib>
#include <cstring>

namespace net::ip::address
{

Custom::Custom()
{

}

Custom::Custom(const char * value)
{
    for (int i = 0; i < 4; i++)
    {
        _data[i] = _withdraw(value, i);
    }
}

Custom::~Custom()
{

}

bool Custom::operator==(const Custom & other)
{
    return memcmp(_data, other._data, 4) == 0;
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
            if (value[i] == '.') counter++;
            if (counter == index)
            {
                pointer = (char * ) &value[i + 1];
                break;
            }
        }
    }

    return (unsigned char) strtol(pointer, nullptr, 10);
}

}; /* namespace: net::ip */
