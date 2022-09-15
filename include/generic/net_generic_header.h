#ifndef _net_generic_header_h
#define _net_generic_header_h

/**
 * @file	net_generic_header.h
 * @author	en2
 * @date	14-09-2022
 * @brief	
 * @details	
**/

namespace net::generic
{

class Header
{
public:
    Header();
    ~Header();

    unsigned char * payload;

}; /* class: Header */

}; /* namespace: net::generic */

#endif /* define: net_generic_header_h */