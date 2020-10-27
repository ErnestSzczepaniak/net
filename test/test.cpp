#include "test.h"
#include "net.h"

bool send(unsigned char * buffer, int size)
{

    return true;
}

bool read(unsigned char * to, int sector)
{
    return true;
}

bool write(unsigned char * from, int sector)
{

    return true;
}

TEST_CASE("test_case_name")
{
    auto server = net::aoe::stack::Server(1, 1, 128, send, read, write);

    server.init();
}