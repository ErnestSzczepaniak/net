#include "test.h"
#include "net.h"

TEST_CASE("test ip")
{
    unsigned char buffer[] = {
        0x08, 0x5b, 0xd6, 0xc6, 0x9a, 0xbc, 0x14, 0xcc, 
        0x20, 0xd1, 0x1b, 0x18, 0x08, 0x00, 0x45, 0x00, 
        0x00, 0x34, 0x19, 0xfc, 0x00, 0x00, 0xf5, 0x06, 
        0xf3, 0x32, 0x34, 0x54, 0xc2, 0x2b, 0xc0, 0xa8, 
        0x01, 0x6d, 0x01, 0xbb, 0xe0, 0x5e, 0x69, 0xeb, 
        0xd1, 0x2c, 0xd4, 0x12, 0x84, 0x2b, 0x80, 0x11, 
        0x00, 0x93, 0x72, 0xf6, 0x00, 0x00, 0x01, 0x01, 
        0x08, 0x0a, 0x93, 0xd9, 0xcd, 0xf6, 0xc7, 0xda, 
        0xab, 0x82, 0x30, 0x79
    };

    auto header_eth = net::eth::Header(buffer);
    auto header_ip = net::ip::Header(header_eth.payload);

    REQUIRE(header_ip.version == 4);
    REQUIRE(header_ip.header_length == 5);
    REQUIRE(header_ip.dscp == 0);
    REQUIRE(header_ip.ecn == net::ip::Ecn::NON_ECN_CAPABLE_TRANSPORT);
    REQUIRE(header_ip.total_length == 52);
    REQUIRE(header_ip.identification == 0x19fc);
    REQUIRE(header_ip.dont_fragment == false);
    REQUIRE(header_ip.more_fragments == false);
    REQUIRE(header_ip.fragment_offset == 0);
    REQUIRE(header_ip.time_to_live == 245);
    REQUIRE(header_ip.protocol == net::ip::Protocol::TCP);
    REQUIRE(header_ip.header_checksum == 0xf332);
    REQUIRE(header_ip.address_source == "52.84.194.43");
    REQUIRE(header_ip.address_destination == "192.168.1.109");
}

