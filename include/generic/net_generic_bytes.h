#ifndef _net_generic_bytes_h
#define _net_generic_bytes_h

/**
 * @file	net_generic_bytes.h
 * @author	en2
 * @date	14-09-2022
 * @brief	
 * @details	
**/

#include "net_generic_field.h"

namespace net::generic
{

template<typename T, int offset, bool reverse>
class Bytes : public Field<T, Bytes<T, offset, reverse>>
{
public:
    Bytes(unsigned char * buffer);
    ~Bytes();

    operator T() const;
    Bytes & operator=(const T & value);
    
protected:
    auto _load() const;
    void _store(const T & value);

    T _invert(T value) const;

private:
    unsigned char * _buffer;

}; /* class: Bytes */

template<typename T, int offset, bool reverse>
Bytes<T, offset, reverse>::Bytes(unsigned char * buffer) : 
Field<T, Bytes<T, offset, reverse>>(this), 
_buffer(buffer)
{

}

template<typename T, int offset, bool reverse>
Bytes<T, offset, reverse>::~Bytes()
{
    
}

template<typename T, int offset, bool reverse>
Bytes<T, offset, reverse>::operator T() const
{
    return _load();
}

template<typename T, int offset, bool reverse>
Bytes<T, offset, reverse> & Bytes<T, offset, reverse>::operator=(const T & value)
{
    _push(value);

    return *this;
}

/* ---------------------------------------------| private |--------------------------------------------- */

template<typename T, int offset, bool reverse>
auto Bytes<T, offset, reverse>::_load() const
{
    T temp;

    memcpy(&temp, &_buffer[offset], sizeof(T));

    if constexpr (reverse) temp = _invert(temp);

    return temp;
}

template<typename T, int offset, bool reverse>
void Bytes<T, offset, reverse>::_store(const T & value)
{
    if constexpr (reverse) value = _invert(value);

    memcpy(&_buffer[offset], &value, sizeof(T));
}

template<typename T, int offset, bool reverse>
T Bytes<T, offset, reverse>::_invert(T value) const
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

}; /* namespace: net::generic */

#endif /* define: net_generic_bytes_h */