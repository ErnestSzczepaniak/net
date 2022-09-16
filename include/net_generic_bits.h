#ifndef _net_bitfield_h
#define _net_bitfield_h

/**
 * @file	net_bitfield.h
 * @author	en2
 * @date	19-10-2020
 * @brief	
 * @details	
**/

#include "net_generic_field.h"

namespace net::generic
{

template<typename T, int byte, int offset, int span>
class Bits : public Field<T, Bits<T, byte, offset, span>>
{
public:
    Bits(unsigned char * buffer);
    ~Bits();

    operator T();
    Bits & operator=(const T & value);

protected:
    auto _load();
    template<typename U> void _store(const U & value);

    auto _mask();

private:
    unsigned char * _buffer;

}; /* class: Bits */

template<typename T, int byte, int offset, int span>
Bits<T, byte, offset, span>::Bits(unsigned char * buffer) : 
Field<T, Bits<T, byte, offset, span>>(this),
_buffer(buffer)
{

}

template<typename T, int byte, int offset, int span>
Bits<T, byte, offset, span>::~Bits()
{

}


template<typename T, int byte, int offset, int span>
Bits<T, byte, offset, span>::operator T()
{
    auto mask = _mask();

    auto value = _load();

    return (T) ((value >> offset) & mask);
}

template<typename T, int byte, int offset, int span>
Bits<T, byte, offset, span> & Bits<T, byte, offset, span>::operator=(const T & value)
{
    auto mask = _mask();

    auto current = _load();

    current &= ~(mask << offset);

    current |= (value & mask) << offset;

    _store(current);

    return *this;
}

/* ---------------------------------------------| private |--------------------------------------------- */

template<typename T, int byte, int offset, int span>
auto Bits<T, byte, offset, span>::_load()
{
    if constexpr (offset + span <= 8)
    {
        return _buffer[byte];   
    }
    else if constexpr (offset + span <= 16) 
    {
        unsigned char b0 = _buffer[byte - 1];
        unsigned char b1 = _buffer[byte];

        return (unsigned short int) ((b0 << 8) | b1);
    }
    else if constexpr (offset + span <= 32) 
    {
        unsigned char b0 = _buffer[byte - 3];
        unsigned char b1 = _buffer[byte - 2];
        unsigned char b2 = _buffer[byte - 1];
        unsigned char b3 = _buffer[byte];

        return (unsigned int) ((b0 << 24) | (b1 << 16) | (b2 << 8) | b3);
    }
}

template<typename T, int byte, int offset, int span>
template<typename U>
void Bits<T, byte, offset, span>::_store(const U & value)
{
    if constexpr (offset + span <= 8)
    {
        _buffer[byte] = value;   
    }
    else if constexpr (offset + span <= 16) 
    {
        unsigned char b0 = (value >> 8) & 0xff;
        unsigned char b1 = value & 0xff;

        _buffer[byte - 1] = b0;
        _buffer[byte] = b1;
    }
    else if constexpr (offset + span <= 32) 
    {
        unsigned char b0 = (value >> 24) & 0xff;
        unsigned char b1 = (value >> 16) & 0xff;
        unsigned char b2 = (value >> 8) & 0xff;
        unsigned char b3 = value & 0xff;

        _buffer[byte - 3] = b0;
        _buffer[byte - 2] = b1;
        _buffer[byte - 1] = b2;
        _buffer[byte] = b3;
    }
}

template<typename T, int byte, int offset, int span>
auto Bits<T, byte, offset, span>::_mask()
{
    if constexpr (offset + span <= 8) return (unsigned char) ((1 << span) - 1);
    else if constexpr (offset + span <= 16) return (unsigned short int) ((1 << span) - 1);
    else if constexpr (offset + span <= 32) return (unsigned int) ((1 << span) - 1);
}

}; /* namespace: net::generic */

#endif /* define: net_bitfield_h */