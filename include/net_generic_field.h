#ifndef _net_generic_field_h
#define _net_generic_field_h

/**
 * @file	net_generic_field.h
 * @author	en2
 * @date	14-09-2022
 * @brief	
 * @details	
**/

#include "string.h"

namespace net::generic
{

template<typename T, typename P>
class Field
{
public:
    Field(P * parent);
    ~Field();

    template<typename U>
    bool operator==(const U & other) const;

    template<typename U>
    bool operator!=(const U & other) const;

private:
    P * _parent;

}; /* class: Field */

template<typename T, typename P>
Field<T, P>::Field(P * parent) : _parent(parent)
{

}

template<typename T, typename P>
Field<T, P>::~Field()
{

}

template<typename T, typename P>
template<typename U>
bool Field<T, P>::operator==(const U & other) const
{
    return (_parent->operator T() == (T) other);
}

template<typename T, typename P>
template<typename U>
bool Field<T, P>::operator!=(const U & other) const
{
    return !operator==(other);
}

}; /* namespace: net::generic */

#endif /* define: net_generic_field_h */