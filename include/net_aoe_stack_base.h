#ifndef _net_aoe_stack_base_h
#define _net_aoe_stack_base_h

/**
 * @file	net_aoe_stack_actor.h
 * @author	en2
 * @date	23-11-2020
 * @brief	
 * @details	
**/

#include "net_interface.h"
#include "net_aoe_stack_code.h"
#include "stdio.h"

namespace net::aoe::stack
{

class Base
{
    static constexpr auto size_buffer = 2048;
    static constexpr unsigned char aoe_version = 1;
    static constexpr unsigned short int firmware_version = 0;

public:
    Base(net::interface::Io & io);

protected:
    void _clear(unsigned char * buffer);

    Code _check_header_eth();
    Code _check_header_aoe(bool response);

    void _fill_header_eth(const eth::address::Custom & destination);
    void _fill_header_aoe(bool response, unsigned char command, unsigned int tag);

    void _fill_header_aoe_query_request();
    void _fill_header_aoe_query_response(unsigned short int buffer_count, unsigned char sector_count);

    void _fill_header_aoe_issue_request(unsigned char sector_count, unsigned char command, unsigned int lba);
    void _fill_header_aoe_issue_response(bool ready, unsigned int lba);

    net::interface::Io & _interface_io;

    unsigned char _input[size_buffer];
    unsigned char _output[size_buffer];

    unsigned short int _major;
    unsigned char _minor;

}; /* class: Actor */

}; /* namespace: net::aoe::stack */


#endif /* define: net_aoe_stack_actor_h */