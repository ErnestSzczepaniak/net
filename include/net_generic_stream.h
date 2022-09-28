#ifndef _net_generic_stream_h
#define _net_generic_stream_h

/**
 * @file	net_generic_stream.h
 * @author	en2
 * @date	16-09-2022
 * @brief	
 * @details	
**/

#include "string.h"
#include <cstdlib>

namespace net::generic
{

template<int size, char separator, int base, bool invert>
class Stream
{
public:
    Stream();
    Stream(const char * value);
    ~Stream();

    bool operator==(const Stream & other) const;

protected:
    unsigned char _pop(const char * value, int index);

private:
    unsigned char _data[size];

}; /* class: Stream */

template<int size, char separator, int base, bool invert>
Stream<size, separator, base, invert>::Stream()
{

}

template<int size, char separator, int base, bool invert>
Stream<size, separator, base, invert>::Stream(const char * value)
{
    if constexpr (invert == false) for (int i = 0; i < size; i++) _data[i] = _pop(value, i);
    else for (int i = 0; i < size; i++) _data[i] = ~_pop(value, i);
}

template<int size, char separator, int base, bool invert>
Stream<size, separator, base, invert>::~Stream()
{

}

template<int size, char separator, int base, bool invert>
bool Stream<size, separator, base, invert>::operator==(const Stream & other) const
{
    return memcmp(_data, other._data, size) == 0;
}

template<int size, char separator, int base, bool invert>
unsigned char Stream<size, separator, base, invert>::_pop(const char * value, int index)
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

#endif /* define: net_generic_stream_h */