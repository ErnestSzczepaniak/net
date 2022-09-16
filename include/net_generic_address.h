#ifndef _net_generic_address_h
#define _net_generic_address_h

/**
 * @file	net_generic_address.h
 * @author	en2
 * @date	16-09-2022
 * @brief	
 * @details	
**/

#include "string.h"
#include <cstdlib>

namespace net::generic
{

template<int size, char separator, int base>
class Address
{
public:
    Address();
    Address(const char * value);
    ~Address();

    bool operator==(const Address & other);

protected:
    unsigned char _pop(const char * value, int index);

private:
    unsigned char _data[size];

}; /* class: Address */


template<int size, char separator, int base>
Address<size, separator, base>::Address()
{

}

template<int size, char separator, int base>
Address<size, separator, base>::Address(const char * value)
{
    for (int i = 0; i < size; i++) _data[i] = _pop(value, i);
}

template<int size, char separator, int base>
Address<size, separator, base>::~Address()
{

}

template<int size, char separator, int base>
bool Address<size, separator, base>::operator==(const Address & other)
{
    return memcmp(_data, other._data, size) == 0;
}

template<int size, char separator, int base>
unsigned char Address<size, separator, base>::_pop(const char * value, int index)
{
    char * pointer = nullptr;

    if (index == 0) pointer = (char * ) value;
    else
    {
        auto counter = 0;

        for (int i = 0; i < strlen(value); i++)
        {
            if (value[i] == separator) counter++;
            if (counter == index)
            {
                pointer = (char * ) &value[i + 1];
                break;
            }
        }
    }

    return strtol(pointer, nullptr, base);
}

}; /* namespace: net::generic */

#endif /* define: net_generic_address_h */