#ifndef _net_aoe_issue_identify_h
#define _net_aoe_issue_identify_h

/**
 * @file	net_aoe_issue_identify.h
 * @author	en2
 * @date	19-10-2020
 * @brief	
 * @details	
**/

#include "net_bytefield.h"
#include "net_aoe_issue.h"

namespace net::aoe::issue::identify
{

using String_serial_number = String<40>;
using String_firmware_revision = String<8>;
using String_model_number = String<40>;

/* ---------------------------------------------| header |--------------------------------------------- */

class Header
{
    using Serial_number = Bytefield<String_serial_number, 20, false>;
    using Firmware_revision = Bytefield<String_firmware_revision, 46, false>;
    using Model_number = Bytefield<String_model_number, 54, false>;
    using Logical_sector_number = Bytefield<unsigned int, 120, false>;

public:
    Header(unsigned char * data) : serial_number(data + position), firmware_revision(data + position),
        model_number(data + position), logical_sector_number(data + position) {}

    Serial_number serial_number;
    Firmware_revision firmware_revision;
    Model_number model_number;
    Logical_sector_number logical_sector_number;

    static constexpr auto position = 36;
    static constexpr auto size = 512;
}; /* class: Header */


}; /* namespace: net::aoe::issue::identify */


#endif /* define: net_aoe_issue_identify_h */