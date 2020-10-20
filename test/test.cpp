#include "test.h"
#include "net.h"

TEST_CASE("test_case_name")
{

    unsigned char buffer[512];

    auto identify = net::aoe::issue::identify::Header(buffer);


    identify.serial_number = net::aoe::issue::identify::String_serial_number("1.1 en2");

}