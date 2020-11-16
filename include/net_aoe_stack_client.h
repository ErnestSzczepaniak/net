#ifndef _net_aoe_stack_client_h
#define _net_aoe_stack_client_h

/**
 * @file	net_aoe_stack_client.h
 * @author	en2
 * @date	04-11-2020
 * @brief	
 * @details	
**/

#include "net_eth.h"

namespace net::aoe::stack
{

class Client
{
    using Handler_receive = bool (*)(unsigned char *, int, int);

public:
    Client();

    void init();

    void read(unsigned char * to, int sector);
    void write(unsigned char * from, int sector);

protected:
    

private:
    

}; /* class: Client */


}; /* namespace: net::aoe::stack */


#endif /* define: net_aoe_stack_client_h */