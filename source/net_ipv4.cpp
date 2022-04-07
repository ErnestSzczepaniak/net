#include "net.h"

namespace net::ipv4
{
    unsigned short int Header::Calc_checksum(unsigned int * ptr, unsigned short len)
    {

        unsigned int ret = 0;
        unsigned long sum = 0;
        unsigned int odd_byte;
        while (len>1)
        {
            sum += *ptr;
            ptr++;
            len-=2;
        }
        if(len ==1){
            *(unsigned char*)(&odd_byte) = *(unsigned char*)ptr;
            odd_byte = (odd_byte>>8)| (odd_byte<<8);
            sum += odd_byte;
        }
        sum = ( sum >> 16) + ( sum & 0xffff);
        sum += (sum >> 16);
        ret =~sum;

        return ret;
    }
}