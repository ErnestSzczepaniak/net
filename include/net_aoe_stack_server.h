#ifndef _net_aoe_stack_server_h
#define _net_aoe_stack_server_h

/**
 * @file	net_aoe_stack_server.h
 * @author	en2
 * @date	27-10-2020
 * @brief	
 * @details	
**/

#include "net_eth.h"

namespace net::aoe::stack
{

class Server
{
    static constexpr auto size_buffer = 2048;
    static constexpr unsigned short int buffer_count = 1;
    static constexpr unsigned short int firmware_version = 0;
    static constexpr unsigned char sector_count = 2;
    static constexpr unsigned char aoe_version = 1;

    using Handler = bool (*)(unsigned char *, int);

public:
    Server(int major, int minor, int sectors, Handler send, Handler read, Handler write);

    void init();
    void process(unsigned char * data);

protected:
    void _fill_header_eth(const eth::address::Custom & destination);
    void _fill_header_aoe(unsigned char command, unsigned int tag);
    void _fill_header_aoe_query();

    bool _check_valid(unsigned char * data);

private:
    unsigned char _buffer[size_buffer];

    unsigned short int _major;
    unsigned char _minor;
    unsigned char _sectors;

    Handler _send;
    Handler _read;
    Handler _write;

}; /* class: Server */


}; /* namespace: net::aoe::stack */


#endif /* define: net_aoe_stack_server_h */