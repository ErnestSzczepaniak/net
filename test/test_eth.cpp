#include "test.h"
#include "net.h"

TEST_CASE("test eth")
{
    unsigned char buffer[] = {
        0x14, 0xcc, 0x20, 0xd1, 0x1b, 0x18, 0x08, 0x5b, 0xd6, 0xc6, 0x9a, 0xbc, 0x08, 0x00, 0x45, 0x00,
        0x00, 0x28, 0x7f, 0xf4, 0x40, 0x00, 0x40, 0x06, 0x37, 0x03, 0xc0, 0xa8, 0x01, 0x6d, 0x14, 0xbd,
        0xad, 0x06, 0xa7, 0xc4, 0x01, 0xbb, 0x78, 0xa2, 0x17, 0x41, 0x1b, 0xaf, 0x46, 0xf5, 0x50, 0x10,
        0x01, 0xf5, 0x83, 0xf3, 0x00, 0x00
    };
 
    auto header_eth = net::eth::Header(buffer);

    REQUIRE(header_eth.address_destination == "14:cc:20:d1:1b:18");
    REQUIRE(header_eth.address_source == "08:5b:d6:c6:9a:bc");
    REQUIRE(header_eth.type == net::eth::Type::IPv4);
}