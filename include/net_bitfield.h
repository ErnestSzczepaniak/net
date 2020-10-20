#ifndef _net_bitfield_h
#define _net_bitfield_h

/**
 * @file	net_bitfield.h
 * @author	en2
 * @date	19-10-2020
 * @brief	
 * @details	
**/

#include "net_field.h"

namespace net
{

template<typename T, int byte, int offset, int span>
class Bitfield : public Field
{
public:
    Bitfield(unsigned char * data) : Field(data) {}

    Bitfield & operator=(const T & value)
    {
        if (sizeof(T) == 1)
        {
            auto mask = (1 << span) - 1;
            _data[byte] &= ~(mask << offset);
            _data[byte] |= ((unsigned char) value << offset);
        }
        else
        {
            
        }

        return *this;
    }
    operator T()
    {
        if (sizeof(T) == 1)
        {
            unsigned char mask = (1 << span) - 1;
            return (T)((_data[byte] >> offset) & mask);
        }
        else
        {
            
        }
    }
    bool operator==(const T & value)
    {
        return (this->operator T() == value);
    }
        bool operator!=(const T & value)
    {
        return !this->operator==(value);
    }

}; /* class: Bitfield */

}; /* namespace: net */

#endif /* define: net_bitfield_h */