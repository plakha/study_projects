#include <stdio.h> /* printf */

#include "ip.h" 

#define RUN_TEST(test) \
    if(!test()) \
    { \
        printf(#test"[OK]\n"); \
    } \
    else \
    { \
        printf(#test"[FAIL]\n"); \
    } \

static const ip_t ref_dec_ip = {{255, 255, 250, 15}};
static int TestBinToDec()
{
    uint32_t ip = 0xFFFFFA0F;
    int i = 0;
    ip_t ret = IPConvertBArrToDotDec(ip);
    
    for (; IPV > i; ++i)
    {
        if (ref_dec_ip.ip_addr[i] != ret.ip_addr[i])
        {
            return 1;
        }
    }
    
    return 0;
    
}

static const uint32_t g_ip_bin = 0xFFFFFA0F;
static int TestDecToBin()
{
    ip_t ip= {{255, 255, 250, 15}};
    uint32_t res = IPConvertDotDecToBArr(ip);
    
    return 0xFFFFFA0F == res ? 0 : 1;
}

static int TestIPIsSame()
{
    ip_t ip1 = {{1, 0, 3, 250}};
    ip_t ip2 = {{10, 0, 3, 250}};
    
    return (IPIsSame(ip1, ip2) ? 1 : 0);
}

int main()
{

    RUN_TEST(TestDecToBin);
    RUN_TEST(TestBinToDec);
    RUN_TEST(TestIPIsSame);
    
    return 0;
}
