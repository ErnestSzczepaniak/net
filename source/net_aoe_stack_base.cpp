#include "net.h"

namespace net::aoe::stack
{

Base::Base(net::interface::Io & interface_io) : _interface_io(interface_io)
{
    _clear(_output);
}

void Base::_clear(unsigned char * buffer)
{
    memset(buffer, 0, size_buffer);
}

void Base::_fill_header_eth(const eth::address::Custom & destination)
{
    auto header_eth = eth::Header(_output);

    header_eth.destination = destination;
    header_eth.source = _interface_io.address();
    header_eth.type = eth::type::Aoe;
}

void Base::_fill_header_aoe(bool response, unsigned char command, unsigned int tag)
{
    auto header_aoe = aoe::Header(_output);

    header_aoe.version = aoe_version;
    header_aoe.flag_response = response;
    header_aoe.flag_error = false;
    header_aoe.error = false;
    header_aoe.address_major = _major;
    header_aoe.address_minor = _minor;
    header_aoe.command = command;
    header_aoe.tag = tag;
}

Code Base::_check_header_eth()
{
    auto header_eth = eth::Header(_input);

    if (header_eth.destination != eth::address::Broadcast && header_eth.destination != _interface_io.address()) 
        return Code::HEADER_ETH_ADDRESS_DESTINATION;
    if (header_eth.type != eth::type::Aoe)
        return Code::HEADER_ETH_TYPE;

    return Code::SUCCESS;
}

Code Base::_check_header_aoe(bool response)
{
    auto header_aoe = aoe::Header(_input);

    if (header_aoe.version != aoe_version) 
        return Code::HEADER_AOE_VERSION;
    if (header_aoe.flag_error == true) 
        return Code::HEADER_AOE_FLAG_ERROR;
    if (header_aoe.flag_response != response) 
        return Code::HEADER_AOE_FLAG_RESPONSE;
    if (header_aoe.error != (unsigned char) 0) 
        return Code::HEADER_AOE_ERROR;

    if (response == false) // if request, check address
    {
        if (header_aoe.address_major != _major && header_aoe.address_major != (unsigned short int) 0xffff) 
            return Code::HEADER_AOE_ADDRESS_MAJOR;
        if (header_aoe.address_minor != _minor && header_aoe.address_minor != (unsigned char) 0xff) 
            return Code::HEADER_AOE_ADDRESS_MINOR;
    }

    return Code::SUCCESS;
}

void Base::_fill_header_aoe_query_request()
{
    _fill_header_aoe_query_response(0, 0);
}

void Base::_fill_header_aoe_query_response(unsigned short int buffer_count, unsigned char sector_count)
{
    auto header_query = aoe::query::Header(_output);

    header_query.buffer_count = buffer_count;
    header_query.firmware_version = firmware_version;
    header_query.sector_count = sector_count;
    header_query.aoe_version = aoe_version;
    header_query.command = aoe::query::command::Read_config_string;
    header_query.config_string_length = 0;
}

void Base::_fill_header_aoe_issue_request(unsigned char sector_count, unsigned char command, unsigned int lba)
{
    auto header_issue = aoe::issue::Header(_output);

    header_issue.sector_count = sector_count;
    header_issue.command = command;
    header_issue.lba = lba;
}

void Base::_fill_header_aoe_issue_response(bool ready, unsigned int lba)
{
    auto header_issue = aoe::issue::Header(_output);

    if (ready == true) header_issue.status_device_ready = true;
    else header_issue.status_error = true;

    header_issue.lba = lba;
}

}; /* namespace: net::aoe::stack */
