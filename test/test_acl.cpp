#include "test.h"
#include "net.h"

TEST_CASE("test acl")
{
    net::acl::Instance acl;

    acl.add("permit tcp any any eq 80");
}