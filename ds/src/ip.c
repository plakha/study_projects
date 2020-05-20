/***********************************
Utility Library for DHCP
***********************************/

#include <assert.h> /* assert */
#include <stddef.h> /* size_t*/

#include "dhcp.h" /* uint32_t, ip_t */

#include "ip.h"

#define BITS_PER_BYTE (8)
#define MASK_BYTE (0xFF)

ip_t IPConvertBArrToDotDec(uint32_t ip)
{
    ip_t res = {{0}};
    int i = IPV - 1;
    uint32_t ith_byte = 0x0;
    
    for (; 0 <= i; --i)
    {
        ith_byte = ip & MASK_BYTE;
        res.ip_addr[i] = ith_byte;
        ip >>= BITS_PER_BYTE;
    }
    assert(!ip);
    
    return res;
}

uint32_t IPConvertDotDecToBArr(ip_t ip)
{
    uint32_t res = 0x0;
    uint32_t ith_byte = 0x0; 
    int i = 0;
    
    for (; IPV > i; ++i)
    {
        res <<= BITS_PER_BYTE;
        ith_byte = ip.ip_addr[i];
        res = (res | ith_byte);
    }
    
    return res;
}

int IPIsSame(ip_t ip1, ip_t ip2)
{
    return (ip1.ip_addr[0] == ip2.ip_addr[0]
         && ip1.ip_addr[1] == ip2.ip_addr[1]
         && ip1.ip_addr[2] == ip2.ip_addr[2]
         && ip1.ip_addr[3] == ip2.ip_addr[3]);
}
