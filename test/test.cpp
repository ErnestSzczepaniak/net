#include "test.h"
#include "net.h"

class Interface_io : public net::interface::Io
{
public:
    virtual int transmitt(unsigned char *, int, int)
    {
        return 0;
    }
    virtual int receive(unsigned char *, int)
    {
        return 0;
    }
    virtual void print(char *)
    {

    }
    virtual net::eth::address::Custom & address()
    {
        return net::eth::address::Empty;
    }

}; /* class: Interface */

class Interface_server : public net::aoe::stack::interface::Server
{
public:
    virtual bool read(unsigned char *, int)
    {
        return true;
    }

    virtual bool write(unsigned char *, int)
    {
        return true;
    }
    virtual bool erase_unit()
    {
        return true;
    }
    virtual bool erase_sector(int)
    {
        return true;
    }
    virtual unsigned int sector_count()
    {
        return 0;
    }

}; /* class: Interface_server */


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
    Interface_server interface_server;
    Interface_io interface_io;

    auto server = net::aoe::stack::Server(interface_io, interface_server);


    int k = 2;
}