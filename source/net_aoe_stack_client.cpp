#include "net.h"

namespace net::aoe::stack
{

Client::Client(net::interface::Io & interface_io) : Base(interface_io)
{
    _major = 0xffff;
    _minor = 0xff;
}

Code Client::connect()
{
    auto size = _get_query_response();

    if (size == -1) return Code::IO_TIMEOUT;
    if (size == 0) return Code::IO_RX;
    if (size != 64) return Code::IO_SIZE;
    if (aoe::Header(_input).command != aoe::command::Query_config_information) return Code::HEADER_AOE_COMMAND;

    _destination = eth::Header(_input).source;
    _major = aoe::Header(_input).address_major;
    _minor = aoe::Header(_input).address_minor;

    size = _get_identify_response();

    if (size == -1) return Code::IO_TIMEOUT;
    if (size == 0) return Code::IO_RX; 
    if (size != 552) return Code::IO_SIZE;

    if (aoe::Header(_input).command != aoe::command::Issue_ata_command && 
        aoe::issue::Header(_input).command != aoe::issue::command::Identify_Device) return Code::HEADER_ATA_COMMAND;

    _sectors = aoe::issue::identify::Header(_input).logical_sector_number;

    return Code::SUCCESS;
}

Code Client::read(unsigned char * to, unsigned int sector, int count)
{
    _fill_header_eth(_destination);
    _fill_header_aoe(false, aoe::command::Issue_ata_command, _tag++);
    _fill_header_aoe_issue_request(count, aoe::issue::command::Read_sectors_with_retry, sector);

    _interface_io.transmitt(_output, 36, 100);
    auto size = _interface_io.receive(_input, 10000);

    if (size == -1) return Code::IO_TIMEOUT;
    if (size == 0) return Code::IO_RX;
    if (size != 40 + 512 * count) return Code::IO_SIZE;

    if (auto code = _check_header_eth_response(); code != Code::SUCCESS) return code;
    if (auto code = _check_header_aoe_response(aoe::command::Issue_ata_command, _tag - 1); code != Code::SUCCESS) return code;

    if (aoe::issue::Header(_input).status_device_ready != true) return Code::HEADER_ATA_ISSUE_BUSY;
    if (aoe::issue::Header(_input).lba != sector) return Code::HEADER_ATA_ISSUE_LBA;

    memcpy(to, &_input[36], count * 512);

    return Code::SUCCESS;
}

Code Client::write(unsigned char * from, unsigned int sector, int count)
{
    _fill_header_eth(_destination);
    _fill_header_aoe(false, aoe::command::Issue_ata_command, _tag++);
    _fill_header_aoe_issue_request(count, aoe::issue::command::Write_sectors_with_retry, sector);

    memcpy(&_output[36], from, count * 512);

    _interface_io.transmitt(_output, 36 + count * 512, 100);
    auto size = _interface_io.receive(_input, 10000);

    if (size == -1) return Code::IO_TIMEOUT;
    if (size == 0) return Code::IO_RX;
    if (size != 64) return Code::IO_SIZE;

    if (auto code = _check_header_eth_response(); code != Code::SUCCESS) return code;
    if (auto code = _check_header_aoe_response(aoe::command::Issue_ata_command, _tag - 1); code != Code::SUCCESS) return code;

    if (aoe::Header(_input).command != aoe::command::Issue_ata_command) return Code::HEADER_ATA_COMMAND;
    if (aoe::Header(_input).tag != _tag - 1) return Code::HEADER_AOE_TAG;
    if (aoe::issue::Header(_input).status_device_ready != true) return Code::HEADER_ATA_ISSUE_BUSY;
    if (aoe::issue::Header(_input).lba != sector) return Code::HEADER_ATA_ISSUE_LBA;

    return Code::SUCCESS;
}

int Client::_get_query_response()
{
    _clear(_output);

    _fill_header_eth(eth::address::Broadcast);
    _fill_header_aoe(false, aoe::command::Query_config_information, 0);
    _fill_header_aoe_query_request();

    _interface_io.transmitt(_output, 32, 100);

    return _interface_io.receive(_input, 1000);
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
