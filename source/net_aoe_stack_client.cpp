#include "net.h"

namespace net::aoe::stack
{

Client::Client(net::interface::Io & interface_io) : Actor(interface_io)
{
    _major = 0xffff;
    _minor = 0xff;
}

bool Client::connect()
{
    _fill_header_eth(eth::address::Broadcast);
    _fill_header_aoe(false, aoe::command::Query_config_information, 0);
    _fill_header_aoe_query_request();

    _interface_io.transmitt(_output, 32, 100);

    auto size = _interface_io.receive(_input, 100);

    if (size == 0)
    {
        _debug("No data received in 100 ms ...");
        return false;
    }

    if (size != 64)
    {
        _debug("Invalid data length received, got [%d], expected [%d]", size, 64);
        return false;
    }

    if (_check_header_eth() == false)
    {
        _debug("Check ETH header failed ...");
        return false;
    }

    if (_check_header_aoe(true) == false)
    {
        _debug("Check AOE header failed ...");
        return false;
    }

    if (aoe::Header(_input).command != aoe::command::Query_config_information)
    {
        _debug("Invalid command received ...");
        return false;
    }

    // query response received

    _destination = eth::Header(_input).source;
    _major = aoe::Header(_input).address_major;
    _minor = aoe::Header(_input).address_minor;

    _debug("AOE server phy address aquired, %02x:%02x:%02x:%02x:%02x:%02x",
        _destination.value[0], _destination.value[1], _destination.value[2], _destination.value[3], _destination.value[4], _destination.value[5]);
    _debug("AOE server address aquired, major = [0x%04x], minor = [0x%02x]", _major, _minor);

}

}; /* namespace: net::aoe::stack */
