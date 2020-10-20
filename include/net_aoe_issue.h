#ifndef _net_aoe_issue_h
#define _net_aoe_issue_h

/**
 * @file	net_aoe_issue.h
 * @author	en2
 * @date	19-10-2020
 * @brief	
 * @details	
**/

#include "net_bitfield.h"
#include "net_bytefield.h"

namespace net::aoe::issue
{

template<int size>
class String
{
public:
    String() {}
    String(char * string)
    {
        auto length = strlen(string);

        for (int i = 0; i < length / 2; i++)
        {
            _string[i * 2 + 0] = string[i * 2 + 1];
            _string[i * 2 + 1] = string[i * 2 + 0];
        }

        if (length % 2 != 0)
        {
            _string[length] = string[length - 1];
            _string[length - 1] = 32;

            memset(&_string[length + 1], 32, size - length - 1);
        } 
        else memset(&_string[length], 32, size - length);
    }

private:
    char _string[size];

}; /* class: String */

namespace command
{

static constexpr unsigned char NOP = 0x00;
static constexpr unsigned char Atapi_soft_reset = 0x08;
static constexpr unsigned char Recalibrate = 0x10;
static constexpr unsigned char Read_sectors_with_retry = 0x20;
static constexpr unsigned char Read_sectors_no_retry = 0x21;
static constexpr unsigned char Read_long_with_retry = 0x22;
static constexpr unsigned char Read_long_no_retry = 0x23;
static constexpr unsigned char Read_ext = 0x24;
static constexpr unsigned char Write_sectors_with_retry = 0x30;
static constexpr unsigned char Write_sectors_no_retry = 0x31;
static constexpr unsigned char Write_long_with_retry = 0x32;
static constexpr unsigned char Write_long_no_retry = 0x33;
static constexpr unsigned char Write_ext = 0x34;
static constexpr unsigned char Write_verify = 0x3c;
static constexpr unsigned char Read_verify_sectors_with_retry = 0x40;
static constexpr unsigned char Read_verify_sectors_no_retry = 0x41;
static constexpr unsigned char Format_track = 0x50;
static constexpr unsigned char Seek = 0x70;
static constexpr unsigned char Execute_device_diagnostics = 0x90;
static constexpr unsigned char Initialize_device_parameters = 0x91;
static constexpr unsigned char Download_microcode = 0x92;
static constexpr unsigned char Standy_immediate_0 = 0x94;
static constexpr unsigned char Idle_immediate_0 = 0x95;
static constexpr unsigned char Standby_0 = 0x96;
static constexpr unsigned char Idle_0 = 0x97;
static constexpr unsigned char Check_power_mode_0 = 0x98;
static constexpr unsigned char Sleep_0 = 0x99;
static constexpr unsigned char Atapi_packet = 0xa0;
static constexpr unsigned char Atapi_identify_device = 0xa1;
static constexpr unsigned char Atapi_service = 0xa2;
static constexpr unsigned char Smart = 0xb0;
static constexpr unsigned char Read_multiple = 0xc4;
static constexpr unsigned char Write_multiple = 0xc5;
static constexpr unsigned char Set_multiple_mode = 0xc6;
static constexpr unsigned char Read_dma_with_retry = 0xc8;
static constexpr unsigned char Read_dma_no_retry = 0xc9;
static constexpr unsigned char Write_dma_with_retry = 0xca;
static constexpr unsigned char Write_dma_no_retry = 0xcb;
static constexpr unsigned char Door_lock = 0xde;
static constexpr unsigned char Door_unlock = 0xdf;
static constexpr unsigned char Standy_immediate_1 = 0xe0;
static constexpr unsigned char Idle_immediate_1 = 0xe1;
static constexpr unsigned char Standby_1 = 0xe2;
static constexpr unsigned char Idle_1 = 0xe3;
static constexpr unsigned char Read_buffer = 0xe4;
static constexpr unsigned char Check_power_mode_1 = 0xe5;
static constexpr unsigned char Sleep_1 = 0xe6;
static constexpr unsigned char Write_buffer = 0xe8;
static constexpr unsigned char Identify_Device = 0xec;
static constexpr unsigned char Media_eject = 0xed;
static constexpr unsigned char Identify_device_dma = 0xee;
static constexpr unsigned char Set_features = 0xef;
static constexpr unsigned char Security_set_password = 0xf1;
static constexpr unsigned char Security_unlock = 0xf2;
static constexpr unsigned char Security_erase_prepare = 0xf3;
static constexpr unsigned char Security_erase_unit = 0xf4;
static constexpr unsigned char Security_freeze = 0xf5;
static constexpr unsigned char Security_disable_password = 0xf6;

}; /* namespace: command */

/* ---------------------------------------------| header |--------------------------------------------- */

class Header
{
    using Flag_extended = Bitfield<bool, 0, 6, 1>;
    using Flag_asynchronous = Bitfield<bool, 0, 1, 1>;
    using Flag_write = Bitfield<bool, 0, 0, 1>;
    using Error = Bytefield<unsigned char, 1>;
    using Feature = Bytefield<unsigned char, 1>;
    using Sector_count = Bytefield<unsigned char, 2>;
    using Command = Bytefield<unsigned char, 3>;

    using Status_busy = Bitfield<bool, 3, 7, 1>;
    using Status_device_ready = Bitfield<bool, 3, 6, 1>;
    using Status_device_fault = Bitfield<bool, 3, 5, 1>;
    using Status_deffered_write_error = Bitfield<bool, 3, 4, 1>;
    using Status_data_request = Bitfield<bool, 3, 3, 1>;
    using Status_alignment_error = Bitfield<bool, 3, 2, 1>;
    using Status_sense_data_available = Bitfield<bool, 3, 1, 1>;
    using Status_error = Bitfield<bool, 3, 0, 1>;

    using Lba = Bytefield<unsigned int, 4, false>;

public:
    Header(unsigned char * data) : flag_extended(data + position), flag_asynchronous(data + position), flag_write(data + position), error(data + position),
        feature(data + position), sector_count(data + position), command(data + position), status_busy(data + position), status_device_ready(data + position),
        status_device_fault(data + position), status_deffered_write_error(data + position), status_data_request(data + position), 
        status_alignment_error(data + position), status_sense_data_available(data + position), status_error(data + position), lba(data + position) {}

    Flag_extended flag_extended;
    Flag_asynchronous flag_asynchronous;
    Flag_write flag_write;
    Error error;
    Feature feature;
    Sector_count sector_count;
    Command command;
    
    Status_busy status_busy;
    Status_device_ready status_device_ready;
    Status_device_fault status_device_fault;
    Status_deffered_write_error status_deffered_write_error;
    Status_data_request status_data_request;
    Status_alignment_error status_alignment_error;
    Status_sense_data_available status_sense_data_available;
    Status_error status_error;

    Lba lba;   

    static constexpr auto position = 24;
    static constexpr auto size = 12;

}; /* class: Header */

}; /* namespace: net::aoe::issue */

#endif /* define: net_aoe_issue_h */