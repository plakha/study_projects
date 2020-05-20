/************************s
*************************/
#ifndef CALCULATOR_H
#define CALCULATOR_H

enum status {OK, E_MATH, E_SYNTAX, E_MALLOC};

int Calculate(const char *str, double *result);

#endif

/*#ifndef SMC_H*/
/*#define SMC_H*/

/*enum status {OK, SYNTAX_ERR, MATH_ERR, ALLOC_FAIL};*/

/*enum status SMCCalculate(const char *expression, double *result); */
/*#endif*/



