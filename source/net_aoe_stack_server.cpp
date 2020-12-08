#include "net.h"

namespace net::aoe::stack
{

Server::Server(net::interface::Io & interface_io, interface::Server & interface_server)
: Base(interface_io), _interface_server(interface_server)
{
    _major = 1;
    _minor = 1;
}

Code Server::process()
{
    auto size = _interface_io.receive(_input, 0);

    if (size == -1) return Code::IO_TIMEOUT;
    if (size == 0) return Code::IO_RX;
    if (auto code = _check_header_eth_request(); code != Code::SUCCESS) return code;
    if (auto code = _check_header_aoe_request(); code != Code::SUCCESS) return code;

    auto size_tx = 0;

    _fill_header_eth(eth::Header(_input).source);
    _fill_header_aoe(true, aoe::Header(_input).command, aoe::Header(_input).tag);

    if (aoe::Header(_input).command == aoe::command::Query_config_information)
    {
        _fill_header_aoe_query_response(buffer_count, sector_count);
        size_tx = 32;
    }
    else if (aoe::Header(_input).command == aoe::command::Issue_ata_command)
    {
        auto result_io = false;

        if (aoe::issue::Header(_input).command == aoe::issue::command::Identify_Device)
        {
            _fill_data_aoe_issue_identify();

            result_io = true;
            size_tx = 512 + 36;
        }
        else if (aoe::issue::Header(_input).command == aoe::issue::command::Read_sectors_with_retry)
        {
            auto [sector_count, lba] = _get_info_aoe_issue();

            result_io = _fill_data_aoe_issue_read(sector_count, lba);
            size_tx = 36 + 512 * sector_count;
        }
        else if (aoe::issue::Header(_input).command == aoe::issue::command::Write_sectors_with_retry)
        {
            auto [sector_count, lba] = _get_info_aoe_issue();

            result_io = _fill_data_aoe_issue_write(_input, sector_count, lba);
            size_tx = 36;
        }
        else if (aoe::issue::Header(_input).command == aoe::issue::command::Security_clear_sectors)
        {
            auto [sector_count, lba] = _get_info_aoe_issue();

            result_io = _fill_data_aoe_issue_clear(sector_count, lba);
            size_tx = 36;
        }
        else if (aoe::issue::Header(_input).command == aoe::issue::command::Security_erase_unit)
        {
            result_io = _fill_data_aoe_issue_erase();
            size_tx = 36;
        }
        else return Code::HEADER_ATA_COMMAND;

        _fill_header_aoe_issue_response(result_io, aoe::issue::Header(_input).lba);
    }
    else return Code::HEADER_AOE_COMMAND;

    if (_interface_io.transmitt(_output, size_tx, 100) != size_tx) return Code::IO_TX;

    _clear(_output);

    return Code::SUCCESS;
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
        if (_interface_server.read(&_output[i * 512 + 36], lba + i) == false) return false;  
    }

    return true;
}

bool Server::_fill_data_aoe_issue_write(unsigned char * data, unsigned char sector_count, unsigned int lba)
{
    for (int i = 0; i < sector_count; i++) 
    {
        if (_interface_server.write(&data[i * 512 + 36], lba + i) == false) return false;
    }

    return true;
}

bool Server::_fill_data_aoe_issue_clear(unsigned char sector_count, unsigned int lba)
{
    for (int i = 0; i < sector_count; i++)
    {
        if (_interface_server.clear(lba + i) == false) return false;
    }
    
    return true;
}

bool Server::_fill_data_aoe_issue_erase()
{
    return _interface_server.erase();
}

Server::Info Server::_get_info_aoe_issue()
{
    unsigned char sector_count = (unsigned char) aoe::issue::Header(_input).sector_count;
    unsigned int lba = (unsigned int) aoe::issue::Header(_input).lba & 0x00ffffff; 

    return {sector_count, lba};
}

}; /* namespace: net::aoe::stack */
