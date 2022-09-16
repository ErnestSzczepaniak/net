// #ifndef _net_aoe_query_h
// #define _net_aoe_query_h

// /**
//  * @file	net_aoe_query.h
//  * @author	en2
//  * @date	19-10-2020
//  * @brief	
//  * @details	
// **/

// #include "net_bitfield.h"
// #include "net_bytefield.h"

// namespace net::aoe::query
// {

// namespace command
// {

// static constexpr unsigned char Read_config_string = 0;
// static constexpr unsigned char Test_config_string = 1;
// static constexpr unsigned char Test_config_string_prefix = 2;
// static constexpr unsigned char Set_config_string = 3;
// static constexpr unsigned char Force_set_config_string = 4;

// }; /* namespace: command */

// /* ---------------------------------------------| header |--------------------------------------------- */

// class Header
// {
//     using Buffer_count = Bytefield<unsigned short int, 0>;
//     using Firmware_version = Bytefield<unsigned short int, 2>;
//     using Sector_count = Bytefield<unsigned char, 4>;
//     using Aoe_version = Bitfield<unsigned char, 5, 4, 4>;
//     using Command = Bitfield<unsigned char, 5, 0, 4>;
//     using Config_string_length = Bytefield<unsigned short int, 6>;

// public:
//     Header(unsigned char * data) : buffer_count(data + position), firmware_version(data + position), sector_count(data + position),
//         aoe_version(data + position), command(data + position), config_string_length(data + position) {}

//     Buffer_count buffer_count;
//     Firmware_version firmware_version;
//     Sector_count sector_count;
//     Aoe_version aoe_version;
//     Command command;
//     Config_string_length config_string_length;

//     static constexpr auto position = 24;
//     static constexpr auto size = 8;  // !: bez config string

// }; /* class: Custom */

// }; /* namespace: net::aoe::query */


// #endif /* define: net_aoe_query_h */