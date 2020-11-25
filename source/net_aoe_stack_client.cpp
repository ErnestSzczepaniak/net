#include "net.h"

namespace net::aoe::stack
{

Client::Client(net::interface::Io & interface_io) : Actor(interface_io)
{
    _major = 0xffff;
    _minor = 0xff;
}

unsigned int Client::connect()
{
    auto size = _get_query_response();

    if (size == 0)
    {
        _debug("No data received in 100 ms ...");
        return -1;
    }

    if (aoe::Header(_input).command != aoe::command::Query_config_information)
    {
        _debug("Invalid command received ...");
        return -1;
    }

    // query response received

    _destination = eth::Header(_input).source;
    _major = aoe::Header(_input).address_major;
    _minor = aoe::Header(_input).address_minor;

    _debug("AOE server phy address aquired, %02x:%02x:%02x:%02x:%02x:%02x",
        _destination.value[0], _destination.value[1], _destination.value[2], _destination.value[3], _destination.value[4], _destination.value[5]);
    _debug("AOE server address aquired, major = [0x%04x], minor = [0x%02x]", _major, _minor);


    size = _get_identify_response();

    if (size == 0)
    {
        _debug("No data received in 100 ms ...");
        return -1;
    }

    if (aoe::Header(_input).command != aoe::command::Issue_ata_command && aoe::issue::Header(_input).command != aoe::issue::command::Identify_Device)
    {
        _debug("Invalid command received ...");
        return -1;
    }  

    _sectors = aoe::issue::identify::Header(_input).logical_sector_number;

    _debug("AOE server logical sector number aquired as [%d]", _sectors);

    _debug("Client succesfully connected !");

    return _sectors;
}

bool Client::read(unsigned char * to, unsigned int sector, int count)
{
    _fill_header_eth(_destination);
    _fill_header_aoe(false, aoe::command::Issue_ata_command, _tag++);
    _fill_header_aoe_issue_request(count, aoe::issue::command::Read_sectors_with_retry, sector);

    _interface_io.transmitt(_output, 36, 100);
    auto size = _interface_io.receive(_input, 10000);

    if (size != 40 + 512 * count)
    {
        _debug("Invalid size received, expected [%d], got [%d] ...", 40 + 512 * count, size);
        return false;
    }

    if (_check_header_eth() == false) return false;
    if (_check_header_aoe_response() == false) return false;

    if (aoe::Header(_input).command != aoe::command::Issue_ata_command)
    {
        _debug("Invalid ATA command received ...");
        return false;
    } 

    if (aoe::Header(_input).tag != _tag - 1)
    {
        _debug("Invalid tag received, expected [%d], got [%d]", _tag - 1, aoe::Header(_input).tag);
        return false;
    }

    if (aoe::issue::Header(_input).status_device_ready != true)
    {
        _debug("Server not ready ...");
        return false; // w response jest status
    }

    if (aoe::issue::Header(_input).lba != sector)
    {
        _debug("Invalid lba received ...");
        return false;
    } 

    memcpy(to, &_input[36], count * 512);

    return true;
}

bool Client::write(unsigned char * from, unsigned int sector, int count)
{
    _fill_header_eth(_destination);
    _fill_header_aoe(false, aoe::command::Issue_ata_command, _tag++);
    _fill_header_aoe_issue_request(count, aoe::issue::command::Write_sectors_with_retry, sector);

    memcpy(&_output[36], from, count * 512);

    _interface_io.transmitt(_output, 36 + count * 512, 100);
    auto size = _interface_io.receive(_input, 10000);

    if (size != 64)
    {
        _debug("Invalid size received, expected [%d], got [%d] ...", 64, size);
        return false;
    }

    if (_check_header_eth() == false) return false;
    if (_check_header_aoe_response() == false) return false;

    if (aoe::Header(_input).command != aoe::command::Issue_ata_command)
    {
        _debug("Invalid ATA command received ...");
        return false;
    } 

    if (aoe::Header(_input).tag != _tag - 1)
    {
        _debug("Invalid tag received, expected [%d], got [%d]", _tag - 1, aoe::Header(_input).tag);
        return false;
    }

    if (aoe::issue::Header(_input).status_device_ready != true)
    {
        _debug("Server not ready ...");
        return false; // w response jest status
    }

    if (aoe::issue::Header(_input).lba != sector)
    {
        _debug("Invalid lba received ...");
        return false;
    } 

    return true;
}

int Client::_get_query_response()
{
    _clear(_output);

    _fill_header_eth(eth::address::Broadcast);
    _fill_header_aoe(false, aoe::command::Query_config_information, 0);
    _fill_header_aoe_query_request();

    _interface_io.transmitt(_output, 32, 100);

    auto size = _interface_io.receive(_input, 1000);

    return (size == 64);
}

int Client::_get_identify_response()
{
    _clear(_output);

    _fill_header_eth(_destination);
    _fill_header_aoe(false, aoe::command::Issue_ata_command, 0);
    _fill_header_aoe_issue_request(0, aoe::issue::command::Identify_Device, 0);

    _interface_io.transmitt(_output, 36, 100);

    return _interface_io.receive(_input, 1000);
}

}; /* namespace: net::aoe::stack */
