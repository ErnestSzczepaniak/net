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

template<typename T, int byte, bool reverse>
class Bytes : public Field<T, Bytes<T, byte, reverse>>
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

template<typename T, int byte, bool reverse>
Bytes<T, byte, reverse>::Bytes(unsigned char * buffer) : 
Field<T, Bytes<T, byte, reverse>>(this), 
_buffer(buffer)
{

}

template<typename T, int byte, bool reverse>
Bytes<T, byte, reverse>::~Bytes()
{
    
}

template<typename T, int byte, bool reverse>
Bytes<T, byte, reverse>::operator T() const
{
    return _load();
}

template<typename T, int byte, bool reverse>
Bytes<T, byte, reverse> & Bytes<T, byte, reverse>::operator=(const T & value)
{
    _store(value);

    return *this;
}

/* ---------------------------------------------| private |--------------------------------------------- */

template<typename T, int byte, bool reverse>
auto Bytes<T, byte, reverse>::_load() const
{
    T temp;

    memcpy(&temp, &_buffer[byte], sizeof(T));

    if constexpr (reverse) temp = _invert(temp);

    return temp;
}

template<typename T, int byte, bool reverse>
void Bytes<T, byte, reverse>::_store(const T & value)
{
    if constexpr (reverse)
    {
        auto temp = _invert(value);   
        memcpy(&_buffer[byte], &temp, sizeof(T));
    }
    else memcpy(&_buffer[byte], &value, sizeof(T));
}

template<typename T, int byte, bool reverse>
T Bytes<T, byte, reverse>::_invert(T value) const
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