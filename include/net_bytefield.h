#ifndef _net_bytefield_h
#define _net_bytefield_h

/**
 * @file	net_bytefield.h
 * @author	en2
 * @date	19-10-2020
 * @brief	
 * @details	
**/

#include "net_field.h"

namespace net
{

template<typename T, int byte, bool reverse = true>
class Bytefield : public Field
{
public:
    Bytefield(unsigned char * data) : Field(data) {}
    Bytefield & operator=(const T & value)
    {
        if (reverse && sizeof(T) > 1)
        {
            auto temp = _reverse(value);
            unsigned char * ptr = ((unsigned char * )&temp+1);
            for(int i = (sizeof(T)-1); i >= 0; i--)
            {
                _data[byte +i] = *ptr;
                ptr--; 
            }
        }
        else
        {
            unsigned char * ptr = (unsigned char * )&value;
            for(int i = 0 ; i < sizeof(T); i++)
            {
                    _data[byte +i] = *ptr;
                    ptr++; 
            }
        }

        return *this;
    }

    Bytefield & operator=(const Bytefield & value)
    {
        memcmp(&_data[byte], &value._data[byte], sizeof(T));
        return *this;
    }

    operator T()
    {
        T temp;

        unsigned char * ptr = ((unsigned char * )&temp+1);
        for(int i = (sizeof(T)-1); i >= 0; i--)
        {
            _data[byte +i] = *ptr;
            ptr--; 
        }
        //memcpy(&temp, &_data[byte], sizeof(T));

        if (reverse && sizeof(T) > 1) temp = _reverse(temp);

        return temp;
    }

    bool operator==(const T & value)
    {
        if (reverse && sizeof(T) > 1)
        {
            auto temp = _reverse(value);
            return (memcmp(&_data[byte], &temp, sizeof(T)) == 0);
        }
        return (memcmp(&_data[byte], &value, sizeof(T)) == 0);
    }

    bool operator!=(const T & value)
    {
        return !this->operator==(value);
    }

}; /* class: Bytefield */

}; /* namespace: net */

#endif /* define: net_bytefield_h */
