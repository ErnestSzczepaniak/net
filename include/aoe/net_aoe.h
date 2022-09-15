#ifndef _net_aoe_h
#define _net_aoe_h

/**
 * @file	net_aoe.h
 * @author	en2
 * @date	19-10-2020
 * @brief	
 * @details	
**/

#include "net_bitfield.h"
#include "net_bytefield.h"

namespace net::aoe
{

namespace error
{

static constexpr unsigned char Unrecognized_command_code = 1;
static constexpr unsigned char Bad_argument_parameter = 2;
static constexpr unsigned char Device_unavailable = 3;
static constexpr unsigned char Config_string_present = 4;
static constexpr unsigned char Unsupported_version = 5;
static constexpr unsigned char Target_is_reserved = 6;

}; /* namespace: ethernet::aoe::header::error */

namespace command
{

static constexpr unsigned char Issue_ata_command = 0;
static constexpr unsigned char Query_config_information = 1;
static constexpr unsigned char Mac_mask_list = 2;
static constexpr unsigned char Reserved = 3;

}; /* namespace: command */

/* ---------------------------------------------| header |--------------------------------------------- */

class Header
{
    using Version = Bitfield<unsigned char, 0, 4, 4>;
    using Flag_response = Bitfield<bool, 0, 3, 1>;
    using Flag_error = Bitfield<bool, 0, 2, 1>;
    using Error = Bytefield<unsigned char, 1>;
    using Major = Bytefield<unsigned short int, 2>;
    using Minor = Bytefield<unsigned char, 4>;
    using Command = Bytefield<unsigned char, 5>;
    using Tag = Bytefield<unsigned int, 6>;

public:
    Header(unsigned char * data) : 
        version(data + position), flag_response(data + position), flag_error(data + position), error(data + position), 
        address_major(data + position), address_minor(data + position), command(data + position), tag(data + position) {}

    Version version;
    Flag_response flag_response;
    Flag_error flag_error;
    Error error;
    Major address_major;
    Minor address_minor;
    Command command;
    Tag tag;

    static constexpr auto position = 14;
    static constexpr auto size = 10;
}; /* class: Custom */

}; /* namespace: net::aoe */


#endif /* define: net_aoe_h */