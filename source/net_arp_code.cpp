#include "net_arp_code.h"

namespace net::arp
{
    const char * parse(Code value)
    {
        if (value == Code::HEADER_ETH_ADDRESS_DESTINATION) return "Header ETH Address Destination";
        else if (value == Code::HEADER_ETH_ADDRESS_SOURCE) return "Header ETH Address Source";
        else if (value == Code::HEADER_ETH_TYPE) return "Header ETH Type";
        else if (value == Code::HEADER_ARP_HARDWARE_TYPE) return "Header ARP Hardware Type";
        else if (value == Code::HEADER_ARP_PROTOCOL_TYPE) return "Header ARP Protocol Type";
        else if (value == Code::HEADER_ARP_HARDWARE_SIZE) return "Header ARP Hardware Size";
        else if (value == Code::HEADER_ARP_PROTOCOL_SIZE) return "Header ARP Protocol Size";
        else if (value == Code::HEADER_ARP_OPCODE) return "Header ARP Opcode";
        else if (value == Code::HEADER_ARP_SENDER_MAC) return "Header ARP Sender Mac";
        else if (value == Code::HEADER_ARP_SENDER_IP) return "Header ARP Sender IP";
        else if (value == Code::HEADER_ARP_TARGET_MAC) return "Header ARP Target Mac";
        else if (value == Code::HEADER_ARP_TARGET_IP) return "Header ARP Target IP";
        else if (value == Code::IO_TX) return "IO TX";
        else if (value == Code::IO_RX) return "IO RX";
        else if (value == Code::IO_TIMEOUT) return "IO TIMEOUT";
        else if (value == Code::IO_SIZE) return "IO SIZE";
    }
}