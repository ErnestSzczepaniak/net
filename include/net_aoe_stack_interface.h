#ifndef _net_aoe_stack_interface_h
#define _net_aoe_stack_interface_h

/**
 * @file	net_aoe_stack_interface.h
 * @author	en2
 * @date	23-11-2020
 * @brief	
 * @details	
**/

namespace net::aoe::stack::interface
{

class Server
{
public:
    virtual bool read(unsigned char *, int) = 0;
    virtual bool write(unsigned char *, int) = 0;
    virtual bool clear(int) = 0;
    virtual bool erase() = 0;
    virtual unsigned int sector_count() = 0;

}; /* class: Server_interface */

}; /* namespace: net::aoe::stack::interface */


#endif /* define: net_aoe_stack_interface_h */