#include "test.h"
#include "net.h"

TEST_CASE("test spd parser")
{
    auto * record = "10 permit ip host 127.0.0.1 eq 80 192.168.1.1 255.255.255.255 range 0 38 precedence match dscp ef log";

    net::spd::Parser parser;

    auto policy = parser.parse((char *) record);

    REQUIRE(policy.sequence_number == 10);
    REQUIRE(policy.condition == net::spd::Condition::PERMIT);
    REQUIRE(policy.protocol == net::spd::Protocol::IP);
    REQUIRE(policy.source.address == "127.0.0.1");
    REQUIRE(policy.source.wildcard == "0.0.0.0");
    REQUIRE(policy.source.port.operation == net::spd::Port_operation::EQUAL);
    REQUIRE(policy.source.port.value0 == 80);
    REQUIRE(policy.destination.address == "192.168.1.1");
    REQUIRE(policy.destination.wildcard == "255.255.255.255");
    REQUIRE(policy.destination.port.operation == net::spd::Port_operation::RANGE);
    REQUIRE(policy.destination.port.value0 == 0);
    REQUIRE(policy.destination.port.value1 == 38);
    REQUIRE(policy.precedence == net::spd::Precedence::MATCH);
    REQUIRE(policy.dscp == net::spd::Dscp::EF);
    REQUIRE(policy.log == true);
}