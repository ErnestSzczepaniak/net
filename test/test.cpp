#include "test.h"
#include "net_field_byte.h"
#include "net_eth_address.h"

TEST_CASE("test_case_name")
{
    unsigned char buffer[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xbb};

    auto rx = net::field::Byte<net::eth::address::Custom, 0, true>(buffer);

    auto address = net::eth::address::Custom("bb:ff:ff:ff:ff:ff");


    if (rx == net::eth::address::Broadcast)
    {
        
    }

    if (address == "any")
    {

    }


    if (rx == "any")
    {
        rx = address;
    }
    // else if (rx == net::eth::address::Broadcast)
    // {
    //     rx = address;
    // }
    

    // REQUIRE(rx == address);

}