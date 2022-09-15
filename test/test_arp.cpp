#include "test.h"
#include "net.h"

TEST_CASE("test arp receive")
{
    unsigned char buffer[] = {
        0x14, 0xcc, 0x20, 0xd1, 0x1b, 0x18, 0x08, 0x5b, 0xd6, 0xc6, 0x9a, 0xbc, 0x08, 0x06, 0x00, 0x01,
        0x08, 0x00, 0x06, 0x04, 0x00, 0x02, 0x08, 0x5b, 0xd6, 0xc6, 0x9a, 0xbc, 0xc0, 0xa8, 0x01, 0x6d,
        0x14, 0xcc, 0x20, 0xd1, 0x1b, 0x18, 0xc0, 0xa8, 0x01, 0x01
    };

    auto header_eth = net::eth::Header(buffer);
    auto header_arp = net::arp::Header(header_eth.payload);

    REQUIRE(header_arp.hardware_type == net::arp::Hardware_type::ETHERNET);
    REQUIRE(header_arp.protocol_type == net::eth::Type::IPv4);
    REQUIRE(header_arp.hardware_size == 6);
    REQUIRE(header_arp.protocol_size == 4);
    REQUIRE(header_arp.operation == net::arp::Operation::REPLY);
    REQUIRE(header_arp.sender_mac_address == "08:5b:d6:c6:9a:bc");
    REQUIRE(header_arp.sender_ip_address == "192.168.1.109");
    REQUIRE(header_arp.target_mac_address == "14:cc:20:d1:1b:18");
    REQUIRE(header_arp.target_ip_address == "192.168.1.1");
}

TEST_CASE("test arp send")
{
    unsigned char buffer[256] = {0};

    auto header_eth = net::eth::Header(buffer);

    header_eth.address_destination = "14:cc:20:d1:1b:18";
    header_eth.address_source = "08:5b:d6:c6:9a:bc";
}