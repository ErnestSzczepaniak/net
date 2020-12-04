#ifndef _net_aoe_stack_server_h
#define _net_aoe_stack_server_h

/**
 * @file	net_aoe_stack_server.h
 * @author	en2
 * @date	27-10-2020
 * @brief	
 * @details	
**/

#include "net_aoe_stack_base.h"
#include "net_aoe_stack_interface.h"

namespace net::aoe::stack
{

class Server : public Base
{
    static constexpr unsigned short int buffer_count = 1;
    static constexpr unsigned char sector_count = 2;

public:
    Server(net::interface::Io & io, interface::Server & server);

    Code process();

protected:
    void _fill_header_aoe_issue(unsigned int lba, bool ready);

    void _fill_data_aoe_query();
    void _fill_data_aoe_issue_identify();
    bool _fill_data_aoe_issue_read(unsigned char sector_count, unsigned int lba);
    bool _fill_data_aoe_issue_write(unsigned char * data, unsigned char sector_count, unsigned int lba);

private:
    interface::Server & _interface_server;

}; /* class: Server */

}; /* namespace: net::aoe::stack */

#endif /* define: net_aoe_stack_server_h */