/***********************************
State Machine Calculator 14/7
Author Andrei
Reviewer Sasha
***********************************/

#include <math.h> /* pow */
#include <assert.h> /* assert */
#include <stdlib.h> /* strtod */
#include <stddef.h> /* size_t */
#include <limits.h> /* INT_MAX */
#include <string.h> /* strlen */

#include "../include/stack.h" /* stack_t */
#include "../include/calculator.h" /* status {OK, E_MATH, E_SYNTAX, E_MALLOC} */

#define N_STATES (4)
#define CHAR_RANGE (UCHAR_MAX + 1)

enum state {WAIT_NUM, WAIT_OP, TERMINATE, ERROR};

enum truth_value {FALSE};

enum precedence
{
	POW = 2,
	MULTIPL = 3,
	DIVID = 3,
	REMAIND = 3,
	ADD = 4,
	SUBSTRACT = 4,
	EOS = 5,
	DUMMY_PREC = 6
};

enum associativity {LTR, RTL, DUMMY_ASSOC};
	
typedef void (*smhandler_f)(char **expression, stack_t *nums, stack_t *ops);
typedef double (*calchandler_f)(double operand1, double operand2);

struct transition 
{
	enum state next_state[N_STATES];
	smhandler_f SMHandle[N_STATES];
};
 
struct operator
{
	enum precedence precedence;
	enum associativity associativity;
	calchandler_f CalcHandle;
};

static const char *g_arith_ops = "+-*/^";
static struct transition g_transition_table[CHAR_RANGE];
static struct operator g_op_table[CHAR_RANGE];
static enum status g_ret_status = OK;
static enum state g_current_machine_state = WAIT_NUM;
static long count_brackets = 0;

static stack_t *CreateNumStack(size_t n_elements);
static stack_t *CreateOpStack(size_t n_elements);
static void	InitOperatorLUT();
static void InitTransitionTable();
static void	ReturnResult(double *result, stack_t *num_stack);

static void SMParseExpression(char **p_expression, stack_t *nums, stack_t *ops);
static void SMHandleSyntaxError(char **p_expression, 
												stack_t *nums, stack_t *ops);
static void SMHandleNum(char **p_expression, stack_t *nums, stack_t *ops);
static void SMHandleOp(char **p_expression, stack_t *nums, stack_t *ops);
static void SMHandleRBracket(char **p_expression, stack_t *nums, stack_t *ops);
static void SMHandleLBracket(char **p_expression, stack_t *nums, stack_t *ops);
static void SMHandleEOS(char **p_expression, stack_t *nums, stack_t *ops);
static void SMDoNothing(char **p_expression, stack_t *nums, stack_t *ops);

static void	CalcFoldOnce(stack_t *nums, stack_t *ops);
static double CalcHandleMultipl(double operand1, double operand2);
static double CalcHandleAdd(double operand1, double operand2);
static double CalcHandlePow(double operand1, double operand2);
static double CalcHandleDivid(double operand1, double operand2);
static double CalcHandleSubtract(double operand1, double operand2);
static double DoNothing(double operand1, double operand2);
static void PushOp(char *p_expression, stack_t *nums, stack_t *ops);

static stack_t *CreateNumStack(size_t n_elements)
{
	assert(0 < n_elements);

	++n_elements; /* because of EOS */

	return STACKCreate(n_elements, sizeof(double));
}

static stack_t *CreateOpStack(size_t n_elements)
{
	char never_done_operator = 'A';
	stack_t *op_stack = NULL;

	assert(0 < n_elements);

	++n_elements; /* because of EOS */
	switch(NULL != (op_stack = STACKCreate(n_elements, sizeof(unsigned char))))
	{
		case FALSE:
			
			return(NULL);
		default:
 			STACKPush(op_stack, &never_done_operator);
			return(op_stack);
	}
}

static void	InitOperatorLUT()
{
	size_t c = 0;
	for(;CHAR_RANGE > c; ++c)
	{
		g_op_table[c].precedence = DUMMY_PREC;
		g_op_table[c].associativity = DUMMY_ASSOC;
		g_op_table[c].CalcHandle = NULL;
	}

	g_op_table['*'].precedence = MULTIPL;
	g_op_table['*'].associativity = LTR;
	g_op_table['*'].CalcHandle = CalcHandleMultipl;
	
	g_op_table['+'].precedence = ADD;
	g_op_table['+'].associativity = LTR;
	g_op_table['+'].CalcHandle = CalcHandleAdd;
	
	g_op_table['-'].precedence = SUBSTRACT;
	g_op_table['-'].associativity = LTR;
	g_op_table['-'].CalcHandle = CalcHandleSubtract;
	
	g_op_table['/'].precedence = DIVID;
	g_op_table['/'].associativity = LTR;
	g_op_table['/'].CalcHandle = CalcHandleDivid;
	
	g_op_table['^'].precedence = POW;
	g_op_table['^'].associativity = RTL;
	g_op_table['^'].CalcHandle = CalcHandlePow;
	
	g_op_table['('].precedence = EOS;
	g_op_table['('].associativity = RTL;
	g_op_table['('].CalcHandle = DoNothing;
	
	g_op_table['\0'].precedence = EOS;
	g_op_table['\0'].associativity = LTR;
}

static void InitTransitionTable()
{
	size_t c = 0;
	const size_t len_arith = strlen(g_arith_ops);
	
	for(c = 0; CHAR_RANGE > c; ++c)
	{
		(g_transition_table[c].next_state)[WAIT_NUM] = ERROR;
		(g_transition_table[c].next_state)[WAIT_OP] = ERROR;
		(g_transition_table[c].next_state)[ERROR] = ERROR;
		(g_transition_table[c].next_state)[TERMINATE] = TERMINATE;
		(g_transition_table[c].SMHandle)[WAIT_NUM] = &SMHandleSyntaxError;
		(g_transition_table[c].SMHandle)[WAIT_OP] = &SMHandleSyntaxError;
		(g_transition_table[c].SMHandle)[ERROR] = &SMHandleSyntaxError;
		(g_transition_table[c].SMHandle)[TERMINATE] = &SMDoNothing;
	}
	
	(g_transition_table['\0'].next_state)[WAIT_NUM] = ERROR;
	(g_transition_table['\0'].next_state)[WAIT_OP] = TERMINATE;
	(g_transition_table['\0'].next_state)[ERROR] = ERROR;
	(g_transition_table['\0'].SMHandle)[WAIT_NUM] = &SMDoNothing;
	(g_transition_table['\0'].SMHandle)[WAIT_OP] = &SMHandleEOS;
	(g_transition_table['\0'].SMHandle)[TERMINATE] = &SMDoNothing;

	for(c = '0'; '9' >= c; ++c)
	{
		(g_transition_table[c].next_state)[WAIT_NUM] = WAIT_OP;
		(g_transition_table[c].next_state)[WAIT_OP] = ERROR;
		(g_transition_table[c].next_state)[ERROR] = ERROR;
		(g_transition_table[c].SMHandle)[WAIT_NUM] = &SMHandleNum;
		(g_transition_table[c].SMHandle)[WAIT_OP] = &SMHandleSyntaxError;
	}
		
	for(c = 0; len_arith > c; ++c)
	{
		(g_transition_table[(size_t)g_arith_ops[c]].next_state)[WAIT_NUM] = 
																		ERROR;
		(g_transition_table[(size_t)g_arith_ops[c]].next_state)[WAIT_OP] = 
																	WAIT_NUM;
		(g_transition_table[(size_t)g_arith_ops[c]].next_state)[ERROR] = 
																		ERROR;
		(g_transition_table[(size_t)g_arith_ops[c]].SMHandle)[WAIT_NUM] = 
														&SMHandleSyntaxError;
		(g_transition_table[(size_t)g_arith_ops[c]].SMHandle)[WAIT_OP] = 
																	&SMHandleOp;
	}
	
	(g_transition_table['('].next_state)[WAIT_NUM] = WAIT_NUM;
	(g_transition_table['('].next_state)[WAIT_OP] = ERROR;
	(g_transition_table['('].next_state)[ERROR] = ERROR;
	(g_transition_table['('].SMHandle)[WAIT_NUM] = &SMHandleLBracket;
	(g_transition_table['('].SMHandle)[WAIT_OP] = &SMHandleSyntaxError;
	
	(g_transition_table[')'].next_state)[WAIT_NUM] = ERROR;
	(g_transition_table[')'].next_state)[WAIT_OP] = WAIT_OP;
	(g_transition_table[')'].next_state)[ERROR] = ERROR;
	(g_transition_table[')'].SMHandle)[WAIT_NUM] = &SMHandleSyntaxError;
	(g_transition_table[')'].SMHandle)[WAIT_OP] = &SMHandleRBracket;
}

static void	ReturnResult(double *result, stack_t *num_stack)
{
	assert(num_stack);
	assert(result);
	
	*result = *(double *)STACKPeek(num_stack);
}

static void SMParseExpression(char **p_expression, stack_t *nums, stack_t *ops)
{
	char curr_input = '\0';
	
	while(OK == g_ret_status 
			&& TERMINATE != g_current_machine_state 
			&& ERROR != g_current_machine_state)
	{
		curr_input = **p_expression;
		g_transition_table[(size_t)curr_input].
				SMHandle[g_current_machine_state](p_expression, nums, ops);
		g_current_machine_state = g_transition_table[(size_t)curr_input]. 
										next_state[g_current_machine_state];
	}
}

static void SMHandleSyntaxError(char **p_expression, stack_t *nums, stack_t *ops)
{
	(void)p_expression;
	(void)nums;
	(void)ops;
	g_ret_status = E_SYNTAX;
}

static void SMHandleNum(char **p_expression, stack_t *nums, stack_t *ops)
{
	double num = 0;
	
	(void)ops;
	(void)p_expression;
	num = strtod(*p_expression, p_expression);
	STACKPush(nums, &num);
}

static void SMHandleOp(char **p_expression, stack_t *nums, stack_t *ops)
{
	PushOp(*p_expression, nums, ops);
	++(*p_expression);
}

static void SMHandleRBracket(char **p_expression, stack_t *nums, stack_t *ops)
{
	assert(')' == **p_expression);
	
	--count_brackets;
	
	while(OK == g_ret_status && 1 < STACKSize(ops) && '(' != *(char *)STACKPeek(ops))
	{
		CalcFoldOnce(nums, ops);
	}
	if(E_MATH == g_ret_status)
	{		
		return;
	}
	
	if('(' == *(char *)STACKPeek(ops))
	{
		STACKPop(ops);
	}
	else
	{
		g_ret_status = E_SYNTAX;
		g_current_machine_state = ERROR;
	}
	
	++(*p_expression);
}

static void SMHandleLBracket(char **p_expression, stack_t *nums, stack_t *ops)
{
	assert('(' == **p_expression);
	
	(void)nums;
	++count_brackets;
	STACKPush(ops, *p_expression);
	++(*p_expression);
}

static void SMHandleEOS(char **p_expression, stack_t *nums, stack_t *ops)
{	
	(void)p_expression;
	
	if(0 != count_brackets)
	{
		g_ret_status = E_SYNTAX;
	}
	
	while(OK == g_ret_status && 1 < STACKSize(ops))
	{
		assert(1 < STACKSize(ops));
		CalcFoldOnce(nums, ops);
	}
}

static void SMDoNothing(char **p_expression, stack_t *nums, stack_t *ops)
{
	(void)p_expression;
	(void)nums;
	(void)ops;
}

static void	CalcFoldOnce(stack_t *nums, stack_t *ops)
{
	double operand1 = 0.0, operand2 = 0.0, result = 0.0;
	char operator = '\0';

	assert(NULL != nums);
	assert(NULL != ops);
	assert(0 != STACKSize(nums));

	operand2 = *(double *)STACKPeek(nums);
	STACKPop(nums);

	operand1 = *(double *)STACKPeek(nums);
	STACKPop(nums);

	operator = *(char *)STACKPeek(ops);
	STACKPop(ops);
	
	result = g_op_table[(size_t)operator].CalcHandle(operand1, operand2);
	STACKPush(nums, &result);
}

static double CalcHandleMultipl(double operand1, double operand2)
{
	return operand1 * operand2;
}

static double CalcHandleAdd(double operand1, double operand2)
{
		return operand1 + operand2;
}

static double CalcHandlePow(double operand1, double operand2)
{
	return pow(operand1, operand2);
}

static double CalcHandleDivid(double operand1, double operand2)
	{
	if(0 == operand2)
	{
		g_ret_status = E_MATH;

		return 0;
	}
			
	return operand1 / operand2;
}

static double CalcHandleSubtract(double operand1, double operand2)
{
	return operand1 - operand2;
}

static double DoNothing(double operand1, double operand2)
{
	(void)operand1;
	(void)operand2;
	
	return 0;
}

static void PushOp(char *expression, stack_t *nums, stack_t *ops)
{
	const char new_operator = *expression;
	
	assert(DUMMY_ASSOC != g_op_table[(size_t)new_operator].associativity);
	assert(DUMMY_PREC != g_op_table[(size_t)new_operator].precedence);
	assert(NULL != g_op_table[(size_t)new_operator].CalcHandle);
	
	switch(g_op_table[(size_t)new_operator].associativity)
	{
		case LTR:
			while(OK == g_ret_status)
			{
				if(g_op_table[(size_t)new_operator].precedence < g_op_table[(size_t)*(char *)STACKPeek(ops)].precedence)
				{
					STACKPush(ops, &new_operator);
					break;
				}
				else
				{
					CalcFoldOnce(nums, ops);
				}
			}
			break;
		case RTL:
			STACKPush(ops, &new_operator);
			break;
		case DUMMY_ASSOC:
			break;
	}

}

int Calculate(const char *expression, double *result)
{
	static int is_table_inited = FALSE;
	stack_t *num_stack = NULL;
	stack_t *op_stack = NULL;
	size_t len_expression = 0;
	char *runner = (char *)expression;
	
	count_brackets = 0;	
	g_current_machine_state = WAIT_NUM;
	g_ret_status = OK;

	switch(len_expression = strlen(expression))
	{
		case 0:
		
			return(E_SYNTAX);
		default:
		;
	}
		
	num_stack = CreateNumStack(len_expression);
	if(NULL == num_stack)
	{
		return(E_MALLOC);
	}
	op_stack = CreateOpStack(len_expression);
	if(NULL == op_stack)
	{
		free(num_stack);
		return(E_MALLOC);
	}

	switch (is_table_inited)
	{	
		case 1:
			break;
		default:
			InitTransitionTable();
			InitOperatorLUT();
			is_table_inited = 1;
	}
			
	SMParseExpression(&runner, num_stack, op_stack);
	
	if(0 != count_brackets)
	{
		g_ret_status = E_SYNTAX;
	}
	if(ERROR != g_current_machine_state && OK == g_ret_status)
	{
		ReturnResult(result, num_stack);
	}
	
	free(num_stack);
	free(op_stack);
	
	return g_ret_status;
}
