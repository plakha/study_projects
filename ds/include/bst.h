#ifndef BST_H
#define BST_H

#include <stdlib.h> /* size_t */

#ifndef CMP_F
#define CMP_F
typedef int (*cmp_f)(const void *data, const void *key, const void *params);
#endif

#ifndef ACT_F 
#define ACT_F
typedef int (*act_f)(void *data, const void *args);
#endif

typedef struct bst_node *bst_it_t;
typedef struct bst bst_t;

/*
enum side{LEFT, RIGHT};
*/

/*
struct bst_node
{
	void *data;
	bst_it_t parent;
	bst_it_t children[2];
};
*/

/*
struct bst
{
	struct bst_node dummy;
	cmp_f compare;
	const void *params;
};
*/

/* returns a BST, compare must be a valid pointer to cmp_f function */
bst_t *BSTCreate(cmp_f compare, const void *params); 

/* destroy bst */
void BSTDestroy(bst_t *bst);

/* return NULL if space is full/failed */
bst_it_t BSTInsert(bst_t *bst, void *data);

/* removes the iterator */
void BSTRemove(bst_it_t node);

/* returns End if not found */
bst_it_t BSTFind(const bst_t *bst, const void *data);

/* 0 succes */
int BSTForEach(bst_it_t from, bst_it_t to, act_f action, const void *args);

/* Mustn't send Begin node*/
bst_it_t BSTPrev(bst_it_t node);

/* Return End iterator if  there is no Next. 
Mustn't send End iterator */
bst_it_t BSTNext(bst_it_t node);

/* Gets Data */
void *BSTGetData(bst_it_t node);

/* How Many Elements */
size_t BSTCount(const bst_t *bst);

/* 0 if FALSE */
int BSTIsEmpty(const bst_t *bst);

/* return iterator to the begin (min) */
bst_it_t BSTBegin(const bst_t *bst);

/* return iterator to the end (dummy)*/
bst_it_t BSTEnd(const bst_t *bst);

#endif


