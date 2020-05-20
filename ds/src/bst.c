/***************************************************
4/7/2019
Iterative implementation of unbalanaced Binary Search Tree (BST)
Author: Andrei
Reviewer: Yoav
***************************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <limits.h> /* INT_MIN */

#include "../include/bst.h" /* bst_it_t */

#define STUB_DATA ((void *)0xDEADBEEF)
#define N_CHILDREN (2)

/*typedef int (*cmp_f)(const void *data, const void *key, const void *params);*/

/*typedef int (*act_f)(void *data, const void *args);*/

/*typedef struct bst_node *bst_it_t;*/
/*typedef struct bst bst_t;*/

enum side {LEFT, RIGHT};
enum status {SUCCESS};

typedef struct bst_node
{
	void *data;
	bst_it_t parent;
	bst_it_t children[2];/* true root is dummy's left child, because successor*/
} bst_node_t;

struct bst
{
	struct bst_node dummy; /* must be first field for BSTGetBegin assert */
	cmp_f compare;
	const void *params;
};

static bst_node_t *CreateNode(const void *data)
{
	size_t i = 0;
	bst_node_t *new_node = NULL;
			
	new_node = (bst_node_t *)malloc(sizeof(*new_node));
	if(NULL == new_node)
	{		
		return(NULL);
	}
	
	new_node->data = (void *)data;
	new_node->parent = NULL;
	for(;N_CHILDREN > i; ++i)
	{
		(new_node->children)[i] = NULL;
	}
	
	return(new_node);
}

static bst_node_t *GetChild(const bst_node_t *node, enum side side)
{
	assert(NULL != node);
	assert(LEFT == side || RIGHT == side);
	
	return((node->children)[side]);
}	

static bst_node_t *GetParent(const bst_node_t *node)
{
	assert(NULL != node);
	
	return(node->parent);
}

static void DestroyNode(bst_node_t *node)
{
	size_t i = 0;
	
	assert(NULL != node);
	
	for(;N_CHILDREN > i; ++i)
	{
		(node->children)[i] = NULL;
	}
	node->data = NULL;
	node->parent = NULL;
	free(node);
	node = NULL;
}

static size_t HowManyChildren(const bst_node_t *node)
{
	size_t i = 0;
	size_t counter = 0;
	
	assert(node != NULL);
	
	for(;N_CHILDREN > i; ++i)
	{
		if(NULL != (node->children)[i])
		{
			++counter;
		}
	}
	
	assert(N_CHILDREN >= counter);
	
	return(counter);
}

static enum side WhichChildIsNode(const bst_node_t *node)
{
	bst_node_t *parent = NULL;
	size_t i = 0;
	
	assert(NULL != node);
	
	parent = GetParent(node);
	assert(NULL != parent);
	
	for(;N_CHILDREN > i; ++i)
	{
		if(GetChild(parent, i) == node)
		{
			assert(N_CHILDREN > i);
			
			return((enum side)i);
		}
	}
	
	return(INT_MAX);
}

static void NodeBypass(bst_node_t *node_to_destroy)
{
	enum side parent_side = INT_MAX;
	bst_node_t *parent = NULL;
	bst_node_t *child = NULL;
	
	assert(NULL != node_to_destroy);
	assert(1 == HowManyChildren(node_to_destroy));
	
	parent = GetParent(node_to_destroy);
	assert(NULL != parent);

	parent_side = WhichChildIsNode(node_to_destroy);
	assert(INT_MAX != parent_side);

	child = GetChild(node_to_destroy, LEFT);
	child = (NULL == child) ? GetChild(node_to_destroy, RIGHT) : child;
	assert(NULL != child);

	child->parent = parent;
	parent->children[parent_side] = child;
	
	DestroyNode(node_to_destroy);
	node_to_destroy = NULL;
}

static bst_node_t *FarthestDescendant(const bst_node_t *node, enum side child)
{
	bst_node_t *runner = NULL;
	
	assert(NULL != node);
	assert(N_CHILDREN > child);

	while(NULL != (runner = GetChild(node, child)))
	{
		node = runner;
	}

	return (bst_node_t *)node;
}

bst_t *BSTCreate(cmp_f compare, const void *params)
{
	size_t i = 0;
	bst_t *bst = NULL;

	assert(NULL != compare);
	
	bst = (bst_t *)malloc(sizeof(*bst));
	if(NULL == bst)
	{
		return(NULL);
	}
	
	bst->dummy.data = STUB_DATA;
	bst->dummy.parent = NULL;
	for(; N_CHILDREN > i; ++i)
	{
		(bst->dummy.children)[i] = NULL;
	}
	bst->compare = compare;
	bst->params = params;
	
	return(bst);
}

void BSTDestroy(bst_t *bst)
{
	assert(NULL != bst);

	while(!BSTIsEmpty(bst))
	{
		BSTRemove(BSTBegin(bst));
	}
	
	free(bst);
	bst = NULL;
}

/* return DUMMY if space is full/failed */
bst_it_t BSTInsert(bst_t *bst, void *new_data)
{
	bst_node_t *runner = NULL;
	bst_node_t *runner_parent = NULL;
	bst_node_t *new_node = NULL;
	bst_node_t *end = NULL;
	int cmp_ret = INT_MIN;
	enum side side = LEFT;
	
	assert(NULL != bst);
	
	end = BSTEnd(bst);
	runner_parent = end; 
	runner = GetChild(runner_parent, LEFT);
	while(NULL != runner)
	{
		cmp_ret = (bst->compare)(BSTGetData(runner), new_data, bst->params);
		if(0 == cmp_ret)
		{
			runner = NULL;
			runner_parent = NULL;
			/* the data has been existed, nothing to do */
			return(end);
		}
		runner_parent = runner;
		side = (0 < cmp_ret) ? LEFT : RIGHT;
		runner = GetChild(runner, side);
	}
	runner = NULL;

	new_node = CreateNode(new_data);
	if(NULL == new_node)
	{
		return(end);
	}

	new_node->parent = runner_parent;
	(runner_parent->children)[side] = new_node;
	runner_parent = NULL;

	return(new_node);	
}

/* removes the iterator */
void BSTRemove(bst_it_t node)
{
	size_t n_children = 0;
	bst_node_t *parent = NULL;
	enum side side = INT_MAX;
	
	assert(NULL != node);
	assert(STUB_DATA != BSTGetData(node));
	
	n_children = HowManyChildren(node);
	parent = GetParent(node);
	side =	WhichChildIsNode(node);
	assert(0 <= side && N_CHILDREN > side);
	
	while(1)
	{
		assert(NULL != node);
		
		/* if the node is leaf */
		if(0 == n_children)
		{
			parent->children[side] = NULL;
			DestroyNode(node);
			node = NULL;
			parent = NULL;
			
			return;
		}
		
		/* if has one child */
		if(1 == n_children)
		{
			NodeBypass(node);
			node = NULL;
			parent = NULL;
			
			return;
		}
		
		/* if has multiple children */
		node->data = BSTGetData(BSTNext(node));
		node = BSTNext(node);
		parent = GetParent(node);
		side =	WhichChildIsNode(node);
		n_children = HowManyChildren(node);
		assert(0 <= side && N_CHILDREN > side);
	}

	node = NULL;
	parent = NULL;
}

bst_it_t BSTFind(const bst_t *bst, const void *data)	
{
	bst_node_t *runner = NULL;
	int cmp_ret = 0;
	
	assert(NULL != bst);

	runner = (bst->dummy.children)[LEFT];
	while(NULL != runner 
	  && 0 != (cmp_ret = (bst->compare)(BSTGetData(runner), data, bst->params)))
	{
		if(0 > cmp_ret)
		{
			runner = GetChild(runner, RIGHT);
		}
		else
		{
			runner = GetChild(runner, LEFT);
		}
	}

	return((NULL == runner) ? BSTEnd(bst) : runner);
}

int BSTForEach(bst_it_t from, bst_it_t to, act_f action, const void *args)
{
	int status = SUCCESS;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action);
	
	while(to != from)
	{
		status = action(BSTGetData(from), args);
		if(SUCCESS != status)
		{
			return(status);
		}
		from = BSTNext(from);
	}
	
	return(status);
}

bst_it_t BSTPrev(bst_it_t node)
{
	bst_node_t *runner = node;
	
	runner = GetChild(node, LEFT);
	if(NULL != runner)
	{
		return(FarthestDescendant(runner, RIGHT));
	}
	
	runner = node;
	while(LEFT == WhichChildIsNode(runner))
	{
		#ifndef NDEBUG
		if(STUB_DATA == BSTGetData(runner))
		{
			assert(BSTBegin((bst_t *)runner) != node);
		}
		#endif
		runner = GetParent(runner);
	}
	
	return(GetParent(runner));		

}

bst_it_t BSTNext(bst_it_t node)
{
	bst_node_t *runner = node;

	assert(NULL != node);
	#ifndef NDEBUG
	if(STUB_DATA == BSTGetData(node))
	{
		assert(BSTEnd((bst_t *)node) != node);
	}
	#endif
	
	runner = GetChild(node, RIGHT);
	if(NULL != runner)
	{
		return(FarthestDescendant(runner, LEFT));
	}
	runner = NULL;

	runner = node;
	while(RIGHT == WhichChildIsNode(runner))
	{
		runner = GetParent(runner);
	}
	
	return(GetParent(runner));	
}

void *BSTGetData(bst_it_t node)
{
	assert(NULL != node);
	
	return(node->data);
}

size_t BSTCount(const bst_t *bst)
{
	bst_node_t *runner= NULL;
	const bst_node_t *end = NULL;
	size_t count = 0;
	
	assert(NULL != bst);
	
	runner = BSTBegin(bst);
	end = BSTEnd(bst);
	while(end != runner)
	{
		++count;	
		runner = BSTNext(runner);
	}
		
	return(count);
}

int BSTIsEmpty(const bst_t *bst)
{	
	assert(NULL != bst);
	
	return(NULL == (bst->dummy.children)[LEFT]);
}

bst_it_t BSTBegin(const bst_t *bst)
{	
	bst_node_t *runner = NULL;
	
	assert(NULL != bst);
	
	runner = (BSTEnd(bst));
	while(NULL != runner->children[LEFT])
	{
		runner = runner->children[LEFT];
	}
	
	return(runner);
}

bst_it_t BSTEnd(const bst_t *bst)
{
	assert(NULL != bst);
	
	return(&((bst_t *)bst)->dummy);
}
