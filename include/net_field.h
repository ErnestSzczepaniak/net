#ifndef _net_field_h
#define _net_field_h

/**
 * @file	net_field.h
 * @author	en2
 * @date	19-10-2020
 * @brief	
 * @details	
**/

#include "string.h"

namespace net
{

class Field
{
public:
    Field(unsigned char * data) : _data(data) {}
    ~Field() {}

protected:
    template<typename T>
    T _reverse(const T & value)
    {
        T temp;

        auto * ptr1 = (unsigned char * ) &value;
        auto * ptr2 = (unsigned char * ) &temp;

        for (int i = 0; i < sizeof(T); i++) ptr2[sizeof(T) - i - 1] = ptr1[i];

        return temp;
    }

    unsigned char * _data;

}; /* class: Field */


}; /* namespace: net */


#endif /* define: net_field_h */