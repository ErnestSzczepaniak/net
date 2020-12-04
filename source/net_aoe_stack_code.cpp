#include "net_aoe_stack_code.h"

namespace net::aoe::stack
{

const char * parse(Code value)
{
    if (value == Code::HEADER_ETH_ADDRESS_DESTINATION) return "Header ETH Address Destination";
    else if (value == Code::HEADER_ETH_ADDRESS_SOURCE) return "Header ETH Address Source";
    else if (value == Code::HEADER_ETH_TYPE) return "Header ETH Type";
    else if (value == Code::HEADER_AOE_VERSION) return "Header AOE Version";
    else if (value == Code::HEADER_AOE_FLAG_ERROR) return "Header AOE Flag Error";
    else if (value == Code::HEADER_AOE_FLAG_RESPONSE) return "Header AOE Flag Response";
    else if (value == Code::HEADER_AOE_ERROR) return "Header AOE Error";
    else if (value == Code::HEADER_AOE_ADDRESS_MAJOR) return "Header AOE Address Major";
    else if (value == Code::HEADER_AOE_ADDRESS_MINOR) return "Header AOE Address Minor";
    else if (value == Code::HEADER_AOE_COMMAND) return "Header AOE Command";
    else if (value == Code::HEADER_AOE_TAG) return "Header AOE Tag";
    else if (value == Code::HEADER_ATA_COMMAND) return "Header ATA Command";
    else if (value == Code::HEADER_ATA_ISSUE_BUSY) return "Header ATA Issue Busy";
    else if (value == Code::HEADER_ATA_ISSUE_LBA) return "Header ATA Issue LBA";
    else if (value == Code::IO_TX) return "IO TX";
    else if (value == Code::IO_RX) return "IO RX";
    else if (value == Code::IO_TIMEOUT) return "IO TIMEOUT";
    else if (value == Code::IO_SIZE) return "IO SIZE";
}

}; /* namespace: net::aoe::stack */
