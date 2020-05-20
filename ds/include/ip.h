/******************************************
*                _____  __     _   ___    *
*               (  _  )(  )   / ) / _ \   *
*    |\---/|     )(_)(  )(__ / _ \\_  /   *
*    | ,_, |    (_____)(____)\___/ (_/    *
*     \_`_/-..----.                       *
*  ___/ `   ' ,""+ \                      *
* (__...'   __\    |`.___.';              *
*  (_,...'(_,.`__)/'.....+                *
*                                         *
*             Exercise: DHCP              *
*             Utility Ip Library          *
******************************************/
#ifndef OL69_IP_H
#define OL69_IP_H

#ifndef IPV
#define IPV (4) /* implementation of 4 byte IP address space */
#endif 

#include "dhcp.h" /* uint32_t, ip_t */


ip_t IPConvertBArrToDotDec(uint32_t ip);

uint32_t IPConvertDotDecToBArr(ip_t ip);

int IPIsSame(ip_t ip1, ip_t ip2);

#endif /* OL69_IP_H */

