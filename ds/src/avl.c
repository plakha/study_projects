/*****************
Recursive implementation of balanced avl binary search tree
*****************/

#include <unistd.h> /* ssize_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <limits.h> /* INT_MAX */

#include "avl.h" /* avl_t */

#define MAX(a,b) ((a > b) ? a : b)

#ifndef NDEBUG
enum truthvalue 
{
	FALSE = 0
};
#endif

enum return_status 
{
	SUCCESS = 0, 
	FAIL,
	NO_NEED
};

enum child_side 
{
	STAY = -1,
	LEFT = 0, 
	RIGHT = 1
};

typedef struct avl_node
{
	void *data;
	struct avl_node *children[2];
	ssize_t height;
} avl_node_t;

 struct avl
{
	avl_node_t *root;
	avl_cmp_f compare;
	const void *params;
};
/*typedef struct avl avl_t;*/

/******************************************************************************/

/* helps AVLDestroy */
static void SubTreeDestroy(avl_node_t *root);

/* helps AVLInsert */
static avl_node_t *NodeCreate(void *data);

static ssize_t GetHeight(const avl_node_t *root);

static const avl_node_t *SubTreeFind(const avl_node_t *root, 
									const void *key, 
									const avl_t *avl);

/* Updates height and also returns the updated height. 
For empty root, return -1.   Helps  Balancing, Rotating */
static ssize_t UpdateHeight (avl_node_t *root);

/* Check if height is right and return balance factor (R - L) */
static ssize_t SubTreeGetBalanceFactor(const avl_node_t *root);

/* Helps AVLGetSize. 
The Caller passes reference to counter initialialized to 0 */
static void SubTreeGetSize(const avl_node_t *root, size_t *counter);

/* Helps AVLDestroy */
static void SubTreeDestroy(avl_node_t *root);

/* Returns child node, respective to the side (LEFT or RIGHT only) */
static avl_node_t *GetChild(const avl_node_t *root, enum child_side side);

/* helps AVLForEach */
static int SubTreeForEach(avl_node_t *root, avl_act_f Act, const void *args);

/* Helps AVLRemove */
static avl_node_t *SubTreeNodeRemove(avl_node_t *root, 
									const void *key, 
									const avl_t *avl);

static avl_node_t *NodeInsert(avl_node_t *root, avl_node_t *new_node, 
							const avl_t *avl, int *p_status);

/* Helps Remove function. Finds the node next to one to remove */
static avl_node_t *GetSuccessor(const avl_node_t *node);

/* Helps GetSuccessor */
static avl_node_t *GetFarthestChild(const avl_node_t *node, 
									enum child_side side);

static enum child_side OtherSide(enum child_side this_side);

static enum child_side WhichChild(int cmp_res);

static avl_node_t *GetAVLRoot(const avl_t *avl);

static void *GetData(const avl_node_t *node);

static int HasTwoChildren(const avl_node_t *node);

static avl_node_t *SubTreeBalance(avl_node_t *root);

static avl_node_t *SubTreeRotate(avl_node_t *root, enum child_side side);
/******************************************************************************/

static avl_node_t *SubTreeBalance(avl_node_t *root)
{
	ssize_t balance_factor = SubTreeGetBalanceFactor(root);
	ssize_t child_balance_factor = 0;
	enum child_side side = STAY;
	enum child_side other_side = STAY;
	
	if (1 < balance_factor)
	{
		side = LEFT;
	}
	else if (-1 > balance_factor)
	{
		side = RIGHT;
	}
	else
	{
		return root;
	}
	
	assert(LEFT == side || RIGHT == side);
	other_side = OtherSide(side);
	child_balance_factor = SubTreeGetBalanceFactor(GetChild(root, other_side));
	if (0 > balance_factor * child_balance_factor)
	{
		root->children[other_side] = SubTreeRotate(GetChild(root, other_side), 
													other_side);
	}
	
	return SubTreeRotate(root, side);
}

static avl_node_t *SubTreeRotate(avl_node_t *root, enum child_side side)
{
	enum child_side other_side = OtherSide(side);
	avl_node_t *pivot = GetChild(root, other_side);
	
	assert ((LEFT == side && RIGHT == other_side)
		|| (RIGHT == side && LEFT == other_side));
	
	root->children[other_side] = GetChild(pivot, side);
	pivot->children[side] = root;
	UpdateHeight(root);
	UpdateHeight(pivot);

	return pivot;
}

static avl_node_t *GetChild(const avl_node_t *root, enum child_side side)
{
	assert(root);
	assert(LEFT == side || RIGHT == side);
	
	return root->children[side];
} 

static ssize_t SubTreeGetBalanceFactor(const avl_node_t *root)
{
	return (UpdateHeight(GetChild(root, RIGHT)) 
			- UpdateHeight(GetChild(root, LEFT)));
}

static void *GetData(const avl_node_t *node)
{
	assert(node);

	return node->data;
}

static avl_node_t *GetAVLRoot(const avl_t *avl)
{
	assert(avl);
	
	return avl->root;
}

avl_t *AVLCreate(avl_cmp_f Compare, const void *params)
{
	avl_t *new_avl = NULL;
	
	assert(Compare);
	
	new_avl = (avl_t *)malloc(sizeof(*new_avl));
	new_avl->root = NULL;
	new_avl->compare = Compare;
	new_avl->params = params;
	
	return new_avl;
}

static void SubTreeDestroy(avl_node_t *root)
{
	if(NULL == root)
	{
		return;
	}
	SubTreeDestroy(root->children[LEFT]);
	root->children[LEFT] = NULL;
	SubTreeDestroy(root->children[RIGHT]);
	root->children[RIGHT] = NULL;
	free(root);
	root = NULL;
}

void AVLDestroy(avl_t *avl)
{
	assert(avl);

	SubTreeDestroy(avl->root);
	free(avl);
	avl = NULL;
}


static avl_node_t *NodeCreate(void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(*new_node));
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->height = 0;
	
	return new_node;
}


static enum child_side WhichChild(int cmp_res)
{
	enum child_side which = STAY;
	
	if(0 < cmp_res)
	{
		which = LEFT;
	}
	else if(0 > cmp_res)
	{
		which = RIGHT;
	}
	
	return which;
}

static enum child_side OtherSide(enum child_side this_side)
{
	switch (this_side)
	{
		case LEFT:
			return RIGHT;
		case RIGHT:
			return LEFT;
		default:
			assert(!FALSE);
		
			return this_side;
	}
}

static avl_node_t *NodeInsert(avl_node_t *root, avl_node_t *new_node, 
							const avl_t *avl, int *p_status)
{
	int cmp_res = -1;
	enum child_side side = STAY;
	
	if (NULL == root)
	{
		assert(SUCCESS == *p_status);
		
		return new_node;
	}
	
	cmp_res = (avl->compare)(GetData(root), GetData(new_node), avl->params);
	side = WhichChild(cmp_res);
	switch (side)
	{
		case STAY:
			assert(0 == cmp_res);
			*p_status = NO_NEED;
			free(new_node);
			new_node = NULL;
			
			return root;
		default :
			assert(0 != cmp_res);
			break ;
	}

	root->children[side] = NodeInsert(GetChild(root, side), 
									new_node, avl, p_status);
	root = SubTreeBalance(root);
	UpdateHeight(root);
	
	return root;
}

int AVLInsert(avl_t *avl, void *data)
{
	int status = SUCCESS;
	avl_node_t *new_node = NodeCreate(data);
	if(!new_node)
	{
		return FAIL;
	}
	
	assert(avl);
	
	avl->root = NodeInsert(GetAVLRoot(avl), new_node, avl, &status);
	
	return status;
}

static avl_node_t *GetFarthestChild(const avl_node_t *node, 
									enum child_side side)
{
	avl_node_t *res = GetChild(node, side); 
	if(NULL == res)
	{
		return (avl_node_t *)node;
	}
	
	return GetFarthestChild(node, side);
}

static avl_node_t *GetSuccessor(const avl_node_t *node)
{
	avl_node_t *successor = NULL;
	
	successor = GetChild(node, RIGHT);
	assert(successor);
	
	return GetFarthestChild(successor, LEFT);
}
	
static int HasTwoChildren(const avl_node_t *node) 
{
	return (GetChild(node, RIGHT) && GetChild(node, LEFT));
	
}

static avl_node_t *SubTreeNodeRemove(avl_node_t *root, 
									const void *key, 
									const avl_t *avl)
{
	avl_node_t *successor =  NULL;
	int cmp_res = 0;
	enum child_side side = STAY;
	
	if(NULL == root)
	{
		return root;
	}
	
	cmp_res = (avl->compare)(GetData(root), key, avl->params);
	side = WhichChild(cmp_res);
	switch (side)
	{
		case STAY:		
			if (HasTwoChildren(root))
			{
				successor = GetSuccessor(root);
				root->data = GetData(successor);
				root->children[RIGHT] = SubTreeNodeRemove(GetChild(root, RIGHT), 
														GetData(successor), 
														avl);
				root = SubTreeBalance(root);
				UpdateHeight(root);			
			}
			else
			{
				successor = GetChild(root, RIGHT);
				successor = (successor) ? (successor) : (GetChild(root, LEFT));
				free(root);
				root = successor;
			}
			
			return root;
		default :
			break ;
	}
	root->children[side] = SubTreeNodeRemove(GetChild(root, side), key, avl);
	root = SubTreeBalance(root);
	UpdateHeight(root);

	return root;	
	
}

void AVLRemove(avl_t *avl, const void *key)
{
	assert(avl);

	avl->root = SubTreeNodeRemove(GetAVLRoot(avl), key, avl);
}

static int SubTreeForEach(avl_node_t *root, avl_act_f Act, const void *args)
{
	int status = SUCCESS;
	
	if(NULL == root)
	{
		return SUCCESS;
	}
	
	status = SubTreeForEach(GetChild(root, LEFT), Act, args);
	if(SUCCESS != status)
	{
		return status;
	}
	
	status = Act(GetData(root), args);
	if(SUCCESS != status)
	{
		return status;
	}
	
	return SubTreeForEach(GetChild(root, RIGHT), Act, args);
}

int AVLForEach(avl_t *avl, avl_act_f Act, const void *args)
{
	assert(avl);
	assert(!AVLIsEmpty(avl));
	assert(Act);
	
	return SubTreeForEach(GetAVLRoot(avl), Act, args);
}

static const avl_node_t *SubTreeFind(const avl_node_t *root, 
									const void *key, 
									const avl_t *avl)
{
	int cmp_res = 0;
	enum child_side side = STAY;
	
	if(NULL == root)
	{
		return NULL;
	}
	
	cmp_res = avl->compare(GetData(root), key, avl->params);
	side = WhichChild(cmp_res);
	switch (side)
	{
		case STAY:
		
			return root;
		default :
			break ;
	}

	return SubTreeFind(GetChild(root, side), key, avl);

}

void *AVLFind(const avl_t *avl, const void *key)
{
	const avl_node_t *found = SubTreeFind(GetAVLRoot(avl), key, avl);
	
	return (found) ? (GetData(found)) : NULL;
}

static void SubTreeGetSize(const avl_node_t *root, size_t *counter)
{
	if(NULL == root)
	{
		return;
	}
	++(*counter);
	SubTreeGetSize(GetChild(root, LEFT), counter);
	SubTreeGetSize(GetChild(root, RIGHT), counter);
}

size_t AVLGetSize(const avl_t *avl)
{
	size_t counter = 0;
	
	assert(avl);
	
	SubTreeGetSize(GetAVLRoot(avl), &counter);
	
	return counter;
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(avl);
	
	return NULL == GetAVLRoot(avl);
}

static ssize_t GetHeight(const avl_node_t *root)
{
	if(NULL == root)
	{
		return -1;
	}
	
	return root->height;
}

static ssize_t UpdateHeight(avl_node_t *root)
{
	if(NULL == root)
	{
		return -1;
	}
	
	root->height = 1 + MAX(GetHeight(GetChild(root, LEFT)), 
						GetHeight(GetChild(root, RIGHT)));
		
	return root->height;
}

size_t AVLGetHeight(const avl_t *avl)
{
	assert(avl);
	
	return (size_t)GetHeight(GetAVLRoot(avl));
}