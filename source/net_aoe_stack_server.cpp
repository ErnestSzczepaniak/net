#include "net.h"

namespace net::aoe::stack
{

Server::Server(net::interface::Io & interface_io, interface::Server & interface_server)
: Actor(interface_io), _interface_server(interface_server)
{
    _major = 1;
    _minor = 1;
}

void Server::process()
{
    auto size = _interface_io.receive(_input, 0);

    if (size == 0) return;
    if (_check_header_eth() == false) return;
    if (_check_header_aoe_request() == false) return;

    _fill_header_eth(eth::Header(_input).source);
    _fill_header_aoe(true, aoe::Header(_input).command, aoe::Header(_input).tag);

    auto size_tx = 0;

    if (aoe::Header(_input).command == aoe::command::Query_config_information)
    {
        _debug("RX: Query config information");

        _fill_header_aoe_query_response(buffer_count, sector_count);

        size_tx = 32;
    }
    else if (aoe::Header(_input).command == aoe::command::Issue_ata_command)
    {
        auto result_io = false;

        if (aoe::issue::Header(_input).command == aoe::issue::command::Identify_Device)
        {
            _debug("RX: Issue identify device");

            _fill_data_aoe_issue_identify();

            result_io = true;
            size_tx = 512 + 36;
        }
        else if (aoe::issue::Header(_input).command == aoe::issue::command::Read_sectors_with_retry ||  aoe::issue::Header(_input).command == aoe::issue::command::Write_sectors_with_retry)
        {
            unsigned char sector_count = (unsigned char) aoe::issue::Header(_input).sector_count;
            unsigned int lba = (unsigned int) aoe::issue::Header(_input).lba & 0x00ffffff;

            if (aoe::issue::Header(_input).command == aoe::issue::command::Read_sectors_with_retry)
            {
                _debug("RX: [R], N = [%d], LBA = [%d]", sector_count, lba);

                result_io = _fill_data_aoe_issue_read(sector_count, lba);
                size_tx = 36 + 512 * sector_count;
            }
            else
            {
                _debug("RX: [W], N = [%d], LBA = [%d]", sector_count, lba);

                result_io = _fill_data_aoe_issue_write(_input, sector_count, lba);
                size_tx = 36;
            }
        }
        else _debug("Invalid ATA command received ...");

        _fill_header_aoe_issue_response(result_io, aoe::issue::Header(_input).lba);
    }
    else _debug("Invalid AOE command received ...");
    
    if (_interface_io.transmitt(_output, size_tx, 100) != size_tx) 
        _debug("Transmitt error, unable to send data ...");

    _clear(_output);
}

/* ---------------------------------------------| info |--------------------------------------------- */

void Server::_fill_data_aoe_issue_identify()
{
    auto header_identify = aoe::issue::identify::Header(_output);

    header_identify.logical_sector_number = _interface_server.sector_count();
}

bool Server::_fill_data_aoe_issue_read(unsigned char sector_count, unsigned int lba)
{
    for (int i = 0; i < sector_count; i++) 
    {
        if (auto result = _interface_server.read(&_output[i * 512 + 36], lba + i); result == false) return false;  
    }

    return true;
}

bool Server::_fill_data_aoe_issue_write(unsigned char * data, unsigned char sector_count, unsigned int lba)
{
    for (int i = 0; i < sector_count; i++) 
    {
        if (auto result = _interface_server.write(&data[i * 512 + 36], lba + i); result == false) return false;
    }

    return true;
}

}; /* namespace: net::aoe::stack */
