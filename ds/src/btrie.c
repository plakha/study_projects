/***********************************
Utility Library for DHCP
***********************************/

#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <limits.h> /* INT_MAX */

#include "btrie.h"

#define BITS_PER_BYTE (8)
#define MASK_BYTE (0xFFU)
#define MASK_BIT (0x1U)
#define FALSE (0)
#define TRUE (1)
#define OK (0)
#define FAIL (1)
#define NONE (0LU)

/******************************************************************************/
static bt_node_t *GetChild(const bt_node_t *root, enum n_th_child child);
static int IsFull(const bt_node_t *root);
static uint32_t NthMask(size_t n_th_bit);
static uint32_t FlipBit(uint32_t bit_arr, size_t n_th_bit);
static enum n_th_child WhichChild(uint32_t bit_arr, size_t n_th_bit);
static enum n_th_child OtherChild(enum n_th_child child);
static bt_node_t *CreateNode();
static int ValidateChildrenExist(bt_node_t *root);
static void UtilRootDestroy(bt_node_t *root);
static void UpdateFullness(bt_node_t *root);
static enum btrie_status UtilBTrieInsert(bt_node_t *root, 
                                         size_t n_bits,
                                         uint32_t bit_arr, 
                                         uint32_t *p_res_bit_arr);
static size_t Pow2(size_t n);
/******************************************************************************/

static bt_node_t *GetChild(const bt_node_t *root, enum n_th_child child)
{
    assert(root);
    
    return root->children[child];
}

static size_t Pow2(size_t n)
{
    assert(1LU << n); /* arithmetic overflow */
    
    return (1LU << n);
}

static int IsFull(const bt_node_t *root)
{
    assert(root);
    
    return root->is_full;
}

static uint32_t NthMask(size_t n_th_bit)
{
    return (MASK_BIT << n_th_bit);
}

static uint32_t FlipBit(uint32_t bit_arr, size_t n_th_bit)
{
    return (bit_arr ^ NthMask(n_th_bit));
}

static enum n_th_child WhichChild(uint32_t bit_arr, size_t n_th_bit)
{
    uint32_t n_th_mask = NthMask(n_th_bit);
    
    return ((bit_arr & n_th_mask) >> n_th_mask);
}

static enum n_th_child OtherChild(enum n_th_child child)
{
    switch (child)
    {
        case ZERO:
            return ONE;
        case ONE:
            return ZERO;
        default :
            assert(FALSE);
            return INT_MAX;
    }
}

static bt_node_t *CreateNode()
{
    bt_node_t *new_node = malloc(sizeof(*new_node));
    if (!new_node)
    {
        return NULL;
    }
    
    new_node->is_full = FALSE;
    new_node->children[ZERO] = NULL;
    new_node->children[ONE] = NULL;
    
    return new_node;
}

static int ValidateChildrenExist(bt_node_t *root)
{
    enum n_th_child i = ZERO;
    int status[N_CHILDREN] = {OK};

    for (; N_CHILDREN > i; ++i)
    {
        if (!GetChild(root, i))
        {
            root->children[i] = CreateNode();
            status[i] = (NULL == GetChild(root, i)) ? FAIL : OK;
        }
    }
    
    return (status[ZERO] || status[ONE]);
}
        
btrie_t *BTrieCreate(size_t n_bits)
{
    btrie_t *new_btrie = NULL;
    
    
    new_btrie = malloc(sizeof(*new_btrie));
    if (!new_btrie)
    {
        return NULL;
    }
        
    new_btrie->root = CreateNode();
    if (!new_btrie->root)
    {
        free(new_btrie);
        new_btrie = NULL;
        
        return NULL;
    }
    
    new_btrie->n_bits = n_bits;
    
    return new_btrie;    
}

static void UtilRootDestroy(bt_node_t *root)
{
    if (!root)
    {
        return ;
    }
    
    UtilRootDestroy(GetChild(root, ZERO));
    root->children[ZERO] = NULL;
    UtilRootDestroy(GetChild(root, ONE));
    root->children[ONE] = NULL;
    free(root);
    root = NULL;
}

void BTrieDestroy(btrie_t *btrie)
{
    assert(btrie);
    
    UtilRootDestroy(btrie->root);
    btrie->root = NULL;
    free(btrie);
    btrie = NULL;
}

static void UpdateFullness(bt_node_t *root)
{
    assert(GetChild(root, ZERO));
    assert(GetChild(root, ONE));
    
    root->is_full = IsFull(GetChild(root, ZERO)) 
                 && IsFull(GetChild(root, ONE));
}

static enum btrie_status UtilBTrieInsert(bt_node_t *root, 
                                         size_t n_bits,
                                         uint32_t bit_arr, 
                                         uint32_t *p_res_bit_arr)
{
    enum n_th_child child = N_CHILDREN;
    enum btrie_status status = OK;
    
    assert(root);
    
    if (IsFull(root))
    {
        return PATH_TAKEN;
    }
    if (!n_bits)
    {
        *p_res_bit_arr = bit_arr;
        root->is_full = TRUE;
        
        return BTRIE_OK;
    }
     
    if(OK != ValidateChildrenExist(root))
    {
        return BTRIE_E_ALLOC;
    }
    
    child = WhichChild(bit_arr, n_bits - 1);
    assert (ZERO == child || ONE == child);
    status = UtilBTrieInsert(GetChild(root, child), n_bits - 1, 
                             bit_arr, p_res_bit_arr);
    switch (status)
    {
        case BTRIE_E_ALLOC:
            return status;
        case BTRIE_OK:
            break ;
        case PATH_TAKEN:
            bit_arr = FlipBit(bit_arr, n_bits - 1);
            status = UtilBTrieInsert(GetChild(root, OtherChild(child)),
                            n_bits - 1,
                            bit_arr,
                            p_res_bit_arr);
            break ;
        default :
            assert(FALSE);
    }
    
    UpdateFullness(root);
    
    return status;
}

enum btrie_status BTrieInsert(btrie_t *btrie, 
                              uint32_t new_bit_arr, 
                              uint32_t *p_res_bit_arr)
{
    enum btrie_status status = BTRIE_OK;
    
    assert(btrie);
    
    if (IsFull(btrie->root))
    {
        return (BTRIE_FULL);
    }
    
    status = UtilBTrieInsert(btrie->root, 
                             btrie->n_bits, 
                             new_bit_arr, 
                             p_res_bit_arr);
    if (BTRIE_E_ALLOC == status)
    {
        return status;
    }
    assert(BTRIE_OK == status || PATH_TAKEN == status);
    
    return ((new_bit_arr == *p_res_bit_arr)
          ? BTRIE_OK
          : PATH_TAKEN);
}

static int UtilBTrieRemove(bt_node_t *root, size_t n_bits, uint32_t key)
{
    int status = OK;
    enum n_th_child child = N_CHILDREN;
    
    if (!root)
    {
        return FAIL;
    }
    if (!n_bits)
    {
        status = IsFull(root) ? OK : FAIL;
        root->is_full = FALSE;
        
        return status;
    }
    
    child = WhichChild(key, n_bits - 1);
    assert(ZERO == child || ONE == child);
    root->is_full = FALSE;
    
    return UtilBTrieRemove(GetChild(root, child), n_bits - 1, key);
}

int BTrieRemove(btrie_t *btrie, uint32_t key)
{
    assert(btrie);
        
    return UtilBTrieRemove(btrie->root, btrie->n_bits, key);
}

static size_t CountTakenPaths(const bt_node_t *root, size_t height)
{
    if (!root)
    {
        return NONE;
    }
    if (IsFull(root))
    {
        return Pow2(height);
    }
    if (!height)
    {
        return NONE;
    }
    
    --height;
    
    return (CountTakenPaths(GetChild(root, ZERO), height)
          + CountTakenPaths(GetChild(root, ONE), height));
    
}

size_t BTrieFreeCount(const btrie_t *btrie)
{
    size_t max_n_paths = NONE;
    
    assert(btrie);
    
    max_n_paths = Pow2(btrie->n_bits);
    assert(max_n_paths);
    
    return (max_n_paths - CountTakenPaths(btrie->root, btrie->n_bits));
}

