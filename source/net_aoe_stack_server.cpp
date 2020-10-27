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
    _fill_header_aoe(command::Query_config_information, 0);
    _fill_header_aoe_query();
    _send(_buffer, 32);
}

void Server::process(unsigned char * data)
{
    if (auto valid = _check_valid(data); valid == false) return;


}

/* ---------------------------------------------| info |--------------------------------------------- */

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

void Server::_fill_header_aoe_query()
{
    auto header_query = aoe::query::Header(_buffer);

    header_query.buffer_count = buffer_count;
    header_query.firmware_version = firmware_version;
    header_query.sector_count = sector_count;
    header_query.aoe_version = aoe_version;
    header_query.command = aoe::query::command::Read_config_string;
    header_query.config_string_length = 0;
}

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


}; /* namespace: net::aoe::stack */
