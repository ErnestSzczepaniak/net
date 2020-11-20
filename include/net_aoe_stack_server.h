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
#include "stdio.h"

namespace net::aoe::stack
{

class Server
{
    static constexpr auto size_buffer = 2048;
    static constexpr unsigned short int buffer_count = 1;
    static constexpr unsigned short int firmware_version = 0;
    static constexpr unsigned char sector_count = 2;
    static constexpr unsigned char aoe_version = 1;

    static constexpr auto timeout = 100;

    using Handler_transmitt = bool (*)(unsigned char *, int, int);
    using Handler_read = bool (*)(unsigned char *, int);
    using Handler_write = bool (*)(unsigned char *, int);
    using Handler_print = void (*)(char *);

public:
    Server(int major, int minor, int sectors, Handler_transmitt transmitt, Handler_read read, Handler_write write, Handler_print print = nullptr);

    void init();
    void process(unsigned char * data);

protected:
    void _clear();
    bool _check_valid(unsigned char * data);

    void _fill_header_eth(const eth::address::Custom & destination);
    void _fill_header_aoe(unsigned char command, unsigned int tag);
    void _fill_header_aoe_issue(unsigned int lba, bool ready);

    void _fill_data_aoe_query();
    void _fill_data_aoe_issue_identify();
    bool _fill_data_aoe_issue_read(unsigned char sector_count, unsigned int lba);
    bool _fill_data_aoe_issue_write(unsigned char * data, unsigned char sector_count, unsigned int lba);

    template<typename ...Args>
    void _debug(const char * format, Args ... args);

private:
    unsigned char _buffer[size_buffer];

    unsigned short int _major;
    unsigned char _minor;
    unsigned int _sectors;

    Handler_transmitt _transmitt;
    Handler_read _read;
    Handler_write _write;
    Handler_print _print;

}; /* class: Server */

template<typename ...Args>
void Server::_debug(const char * format, Args ... args)
{
    if (_print != nullptr)
    {
        char buffer[256];
        
        snprintf(buffer, 256, format, args...);

        _print(buffer);
    }
}

}; /* namespace: net::aoe::stack */

#endif /* define: net_aoe_stack_server_h */