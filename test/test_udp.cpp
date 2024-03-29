#include "test.h"
#include "net.h"

TEST_CASE("test udp")
{
    unsigned char buffer[] = {
        0x14, 0xcc, 0x20, 0xd1, 0x1b, 0x18, 0x08, 0x5b, 0xd6, 0xc6, 0x9a, 0xbc, 0x08, 0x00, 0x45, 0x00,
        0x00, 0x3d, 0xd5, 0xd6, 0x40, 0x00, 0x40, 0x11, 0xe1, 0x40, 0xc0, 0xa8, 0x01, 0x6d, 0xac, 0xd9,
        0x14, 0xaa, 0xe3, 0xbb, 0x01, 0xbb, 0x00, 0x29, 0x83, 0xd3, 0x55, 0x79, 0xc9, 0xdc, 0xc0, 0x75,
        0x06, 0x00, 0x50, 0xdc, 0x48, 0x9e, 0xcb, 0x3f, 0x88, 0x8b, 0x89, 0x9a, 0x18, 0x13, 0x34, 0xe0,
        0x33, 0xe3, 0x73, 0x7b, 0xa9, 0xdd, 0x5a, 0xb9, 0x87, 0xa5, 0x19
    };
 
    auto header_eth = net::eth::Header(buffer);
    auto header_ip = net::ip::Header(header_eth.payload);
    auto header_udp = net::udp::Header(header_ip.payload);

    REQUIRE(header_udp.source_port == 58299);
    REQUIRE(header_udp.destination_port == 443);
    REQUIRE(header_udp.length == 41);
    REQUIRE(header_udp.checksum == 0x83d3);
}