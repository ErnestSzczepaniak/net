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
    bool _check_valid(unsigned char * data);

    void _fill_header_eth(const eth::address::Custom & destination);
    void _fill_header_aoe(unsigned char command, unsigned int tag);
    void _fill_header_aoe_issue(unsigned int lba);

    void _respond_aoe_query();
    void _respond_aoe_issue_identify();
    void _respond_aoe_issue_read(unsigned char sector_count, unsigned int lba);
    void _respond_aoe_issue_write(unsigned char sector_count, unsigned int lba);

private:
    unsigned char _buffer[size_buffer];

    unsigned short int _major;
    unsigned char _minor;
    unsigned short int _sectors;

    Handler _send;
    Handler _read;
    Handler _write;

}; /* class: Server */


}; /* namespace: net::aoe::stack */


#endif /* define: net_aoe_stack_server_h */