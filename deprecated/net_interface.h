#ifndef _net_interface_h
#define _net_interface_h

/**
 * @file	net_interface.h
 * @author	en2
 * @date	23-11-2020
 * @brief	
 * @details	
**/

#include "net_eth.h"

namespace net::interface
{

class Io
{
public:
    virtual int transmitt(unsigned char *, int, int) = 0;
    virtual int receive(unsigned char *, int) = 0;
    virtual eth::address::Custom & address() = 0;

}; /* class: Io */

}; /* namespace: net::interface */

#endif /* define: net_interface_h */