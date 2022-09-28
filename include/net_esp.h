#ifndef _net_esp_h
#define _net_esp_h

/**
 * @file	net_esp.h
 * @author	en2
 * @date	28-09-2022
 * @brief	
 * @details	
**/

#include "net_generic_bytes.h"

namespace net::esp
{

class Header
{
public:
    Header(unsigned char * buffer);
    ~Header();

    generic::Bytes<unsigned int, 0, true> spi;
    generic::Bytes<unsigned int, 4, true> sequence_number;
    
    unsigned char * payload;

}; /* class: Header */

}; /* namespace: net::esp */

#endif /* define: net_esp_h */