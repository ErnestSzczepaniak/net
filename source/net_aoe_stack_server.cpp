#include "net.h"

namespace net::aoe::stack
{

Server::Server(int major, int minor, int sectors, Handler send, Handler read, Handler write)
: _major(major), _minor(minor), _sectors(sectors), _send(send), _read(read), _write(write)
{

}


void Server::init()
{
    _fill_header_eth(eth::address::Broadcast);
    _fill_header_aoe(aoe::command::Query_config_information, 0);
    _respond_aoe_query();
}

void Server::process(unsigned char * data)
{
    if (auto valid = _check_valid(data); valid == false) return;

    _fill_header_eth(eth::Header(data).source);
    _fill_header_aoe(aoe::Header(data).command, aoe::Header(data).tag);

    if (aoe::Header(data).command == aoe::command::Query_config_information)
    {
        _respond_aoe_query();
    }
    else if (aoe::Header(data).command == aoe::command::Issue_ata_command)
    {
        _fill_header_aoe_issue(aoe::issue::Header(data).lba);

        if (aoe::issue::Header(data).command == aoe::issue::command::Identify_Device)
        {
            _respond_aoe_issue_identify();
        }
        else if (aoe::issue::Header(data).command == aoe::issue::command::Read_sectors_with_retry)
        {
            _respond_aoe_issue_read(aoe::issue::Header(data).sector_count, aoe::issue::Header(data).lba);
        }
        else if (aoe::issue::Header(data).command == aoe::issue::command::Write_sectors_with_retry)
        {
            _respond_aoe_issue_write(aoe::issue::Header(data).sector_count, aoe::issue::Header(data).lba);
        }        
    }
}

/* ---------------------------------------------| info |--------------------------------------------- */

bool Server::_check_valid(unsigned char * data)
{
    auto header_eth = eth::Header(data);

    if (header_eth.destination != eth::address::Broadcast && header_eth.destination != eth::address::Empty) return false;
    if (header_eth.type != eth::type::Aoe) return false;

    auto header_aoe = aoe::Header(data);

    if (header_aoe.version != aoe_version) return false;
    if (header_aoe.flag_error == true) return false;
    if (header_aoe.flag_response == true) return false;
    if (header_aoe.error != (unsigned char) 0) return false;
    if (header_aoe.address_major != _major) return false;
    if (header_aoe.address_minor != _minor) return false;

    return true;
}

void Server::_fill_header_eth(const eth::address::Custom & destination)
{
    auto header_eth = eth::Header(_buffer);

    header_eth.destination = destination;
    header_eth.source = eth::address::Empty;
    header_eth.type = eth::type::Aoe;
}

void Server::_fill_header_aoe(unsigned char command, unsigned int tag)
{
    auto header_aoe = aoe::Header(_buffer);

    header_aoe.version = aoe_version;
    header_aoe.flag_response = true;
    header_aoe.error = 0;
    header_aoe.address_major = _major;
    header_aoe.address_minor = _minor;
    header_aoe.command = command;
    header_aoe.tag = tag;
}

void Server::_fill_header_aoe_issue(unsigned int lba)
{
    auto header_issue = aoe::issue::Header(_buffer);

    header_issue.status_device_ready = true;
    header_issue.lba = lba;
}

void Server::_respond_aoe_query()
{
    auto header_query = aoe::query::Header(_buffer);

    header_query.buffer_count = buffer_count;
    header_query.firmware_version = firmware_version;
    header_query.sector_count = sector_count;
    header_query.aoe_version = aoe_version;
    header_query.command = aoe::query::command::Read_config_string;
    header_query.config_string_length = 0;
    
    _send(_buffer, 32);
}

void Server::_respond_aoe_issue_identify()
{
    auto header_identify = aoe::issue::identify::Header(_buffer);

    header_identify.logical_sector_number = _sectors;

    _send(_buffer, 32 + 512);
}

void Server::_respond_aoe_issue_read(unsigned char sector_count, unsigned int lba)
{
    for (int i = 0; i < sector_count; i++) _read(&_buffer[i * 512 + 36], lba + i);

    _send(_buffer, 32 + 512 * sector_count);
}

void Server::_respond_aoe_issue_write(unsigned char sector_count, unsigned int lba)
{
    for (int i = 0; i < sector_count; i++) _write(&_buffer[i * 512 + 36], lba + i);

    _send(_buffer, 32 + 512 * sector_count);
}

}; /* namespace: net::aoe::stack */
