#include "test.h"
#include "net.h"

TEST_CASE("test sad parser")
{
    auto * inbound = "inbound 10.10.10.2 10.10.10.1 0x64548484 0x00000002 60 2048";
    auto * outbound = "outbound 10.10.10.1 192.168.0.1 10.10.10.2 192.168.1.2 0xa22312d1 0x00000009 60 2048";

    net::sad::Parser parser;

    auto inbound_policy = parser.parse((char *) inbound);
    auto outbound_policy = parser.parse((char *) outbound);

    REQUIRE(inbound_policy.traffic == net::sad::Traffic::INBOUND);
    REQUIRE(inbound_policy.source.tunnel.address == "10.10.10.2");
    REQUIRE(inbound_policy.source.local.address == "192.168.0.2");
    REQUIRE(inbound_policy.destination.tunnel.address == "10.10.10.1");
    REQUIRE(inbound_policy.destination.local.address == "192.168.1.1");
    REQUIRE(inbound_policy.spi == 0x64548484);
    REQUIRE(inbound_policy.sequence_number == 0x00000002);
    REQUIRE(inbound_policy.ttl_seconds == 60);
    REQUIRE(inbound_policy.ttl_bytes == 2048);
}