#ifndef _net_field_byte_h
#define _net_field_byte_h

/**
 * @file	net_field_byte.h
 * @author	en2
 * @date	13-09-2022
 * @brief	
 * @details	
**/

#include "string.h"

namespace net::field
{

template<typename T, int offset = 0, bool reverse = false>
class Byte
{
public:
    Byte(unsigned char * buffer);
    ~Byte();

    operator T();
    Byte & operator=(const T & value);
    bool operator==(const T & value);
    bool operator!=(const T & value);

protected:
    T _invert(T value);
    void _push(T value);
    T _pop();

private:
    unsigned char * _buffer;

}; /* class: Byte */

template<typename T, int offset, bool reverse>
Byte<T, offset, reverse>::Byte(unsigned char * buffer) : _buffer(buffer)
{

}

template<typename T, int offset, bool reverse>
Byte<T, offset, reverse>::~Byte()
{
    
}

template<typename T, int offset, bool reverse>
Byte<T, offset, reverse>::operator T()
{
    return _pop();
}

template<typename T, int offset, bool reverse>
Byte<T, offset, reverse> & Byte<T, offset, reverse>::operator=(const T & value)
{
    _push(value);

    return *this;
}

template<typename T, int offset, bool reverse>
bool Byte<T, offset, reverse>::operator==(const T & value)
{
    return (this->operator T() == value);
}

template<typename T, int offset, bool reverse>
bool Byte<T, offset, reverse>::operator!=(const T & value)
{
    return !this->operator==(value);
}

/* ---------------------------------------------| private |--------------------------------------------- */

template<typename T, int offset, bool reverse>
T Byte<T, offset, reverse>::_invert(T value)
{
    T temp;

    auto * ptr_value = (unsigned char *) &value;
    auto * ptr_temp = (unsigned char *) &temp;

    for (int i = 0; i < sizeof(T); i++)
    {
        ptr_temp[sizeof(T) - i - 1] = ptr_value[i];   
    }

    return temp;
}

template<typename T, int offset, bool reverse>
void Byte<T, offset, reverse>::_push(T value)
{
    if constexpr (reverse) value = _invert(value);

    memcpy(&_buffer[offset], &value, sizeof(T));
}

template<typename T, int offset, bool reverse>
T Byte<T, offset, reverse>::_pop()
{
    T temp;

    memcpy(&temp, &_buffer[offset], sizeof(T));

    if constexpr (reverse) temp = _invert(temp);

    return temp;
}

}; /* namespace: net::field */

#endif /* define: net_field_byte_h */