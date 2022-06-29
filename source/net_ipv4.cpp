#include "net.h"
#include <stdint.h>
namespace net::ipv4
{
	unsigned short int Header::Calc_checksum(unsigned int short *ptr, unsigned short len)
	{

		uint16_t ret = 0;
		uint32_t sum = 0;
		uint16_t odd_byte;
		uint16_t swaped;
		while (len > 1)
		{
			swaped = (*ptr >> 8) | (*ptr << 8);
			sum += swaped;
			ptr++;
			len -= 2;
		}
		if (len == 1)
		{
			*(char *)(&odd_byte) = *(char *)ptr;
			odd_byte = (odd_byte >> 8) | (odd_byte << 8);
			sum += odd_byte;
		}
		sum = (sum >> 16) + (sum & 0xffff);
		sum += (sum >> 16);
		ret = ~sum;

		return ret;
	}
}