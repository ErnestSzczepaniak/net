#include "test.h"
#include "net.h"

class Interface_io : public net::interface::Io
{
public:
    virtual int transmitt(unsigned char *, int, int)
    {

    }
    virtual int receive(unsigned char *, int)
    {

    }
    virtual void print(char *)
    {

    }
    virtual net::eth::address::Custom & address()
    {

    }

}; /* class: Interface */

class Interface_server : public net::aoe::stack::interface::Server
{
public:
    virtual bool read(unsigned char *, int)
    {

    }

    virtual bool write(unsigned char *, int)
    {

    }

    virtual unsigned int sector_count()
    {

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