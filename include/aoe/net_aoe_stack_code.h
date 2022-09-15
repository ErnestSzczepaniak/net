#ifndef _net_aoe_stack_code_h
#define _net_aoe_stack_code_h

/**
 * @file	net_aoe_stack_code.h
 * @author	en2
 * @date	02-12-2020
 * @brief	
 * @details	
**/

namespace net::aoe::stack
{

enum class Code : unsigned char
{
    SUCCESS,

    HEADER_ETH_ADDRESS_DESTINATION,
    HEADER_ETH_ADDRESS_SOURCE,
    HEADER_ETH_TYPE,

    HEADER_AOE_VERSION,
    HEADER_AOE_FLAG_ERROR,
    HEADER_AOE_FLAG_RESPONSE,
    HEADER_AOE_ERROR,
    HEADER_AOE_ADDRESS_MAJOR,
    HEADER_AOE_ADDRESS_MINOR,
    HEADER_AOE_COMMAND,
    HEADER_AOE_TAG,

    HEADER_ATA_COMMAND,
    HEADER_ATA_ISSUE_BUSY,
    HEADER_ATA_ISSUE_LBA,

    IO_TX,
    IO_RX,
    IO_TIMEOUT,
    IO_SIZE,

}; /* enum: Result */

const char * parse(Code value);

}; /* namespace: net::aoe::stack */

#endif /* define: net_aoe_stack_code_h */