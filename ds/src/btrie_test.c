#include <stdio.h> /* printf */

#include "btrie.h"

#define RUN_TEST(test) \
    if(!test()) \
    { \
        printf(#test"[OK]\n"); \
    } \
    else \
    { \
        printf(#test"[FAIL]\n"); \
    } \

static int TestCreateDestroy()
{
    btrie_t *btrie = BTrieCreate(3);
    if (!btrie)
    {
        printf("%d alloc fail\n", __LINE__);
    }
    
    BTrieDestroy(btrie);
    btrie = NULL;
    
    return 0;
}

static int TestInsert()
{
    uint32_t output = 0x0;
    uint32_t input = 0x0;
    int status = 0;
    
    btrie_t *btrie = BTrieCreate(1);
    if (!btrie)
    {
        printf("%d alloc fail\n", __LINE__);
    }
    
    status = BTrieInsert(btrie, 0x1, &output);
    printf("status %d,  output %x\n", status, output);
    status = BTrieInsert(btrie, input, &output);
    printf("status %d, , output %x\n", status, output);
    status = BTrieInsert(btrie, 0x1, &output);
    printf("status %d,  output %x\n", status, output);
    
    return 0;
}

int main()
{
    RUN_TEST(TestCreateDestroy);
    RUN_TEST(TestInsert);

    return 0;
}
