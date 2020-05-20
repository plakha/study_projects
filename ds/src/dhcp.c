/* TODO exec indhcp module
    int status[2] = {OK};
    uint32_t dummy[2] = {0x0};
    const uint32_t network_addr = 0x0;
    const uint32_t wild_card = CalcWildCard(n_bits);
    */
    /*TODO exec indhcp module
    status[0] = BTrieInsert(new_btrie, network_addr, dummy);
    status[1] = BTrieInsert(new_btrie, network_addr, dummy + 1);
    if (status[0] || status[1])
    {
        BTrieDestroy(new_btrie);
        new_btrie = NULL;
        
        return NULL;
    }
    
    assert(network_addr == dummy[0]);
    assert(wild_card == dummy[1]);
    */
    
    
    /* static uint32_t CalcWildCard(size_t n_bits)
{
    size_t i = 0;
    uint32_t res = 0x0;
    
    for (; n_bits > i; ++i)
    {
        res <<= 1;
        res |= MASK_BIT;
    }
    
    return res;
} */

