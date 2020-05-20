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
* Exercise: DHCP                          *
* Utility BTrie Library,                  *
* The BTrie is capable to hold bit arrays *
******************************************/
#ifndef OL69_BTRIE_H
#define OL69_BTRIE_H

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t */

enum n_th_child 
{
    ZERO = 0,
    ONE,
    N_CHILDREN
};

enum btrie_status
{
    BTRIE_OK, /* inserted given data */
    PATH_TAKEN, /* data has been already inserted, so inserted something else */
    BTRIE_FULL, /* no place to insert data */
    BTRIE_E_ALLOC /* couldn't allocate memory */
};

typedef struct bt_node
{
    int is_full;
    struct bt_node *children[N_CHILDREN];
} bt_node_t;

typedef struct
{
    size_t n_bits;
    bt_node_t *root;
} btrie_t;

btrie_t *BTrieCreate(size_t n_bits);
void BTrieDestroy(btrie_t *btrie);
enum btrie_status BTrieInsert(btrie_t *btrie, 
                              uint32_t new_bit_arr, 
                              uint32_t *res_bit_arr);
int BTrieRemove(btrie_t *btrie, uint32_t key);
size_t BTrieFreeCount(const btrie_t *btrie);

#endif /* OL69_BTRIE_H */















