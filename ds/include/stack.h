#include <stddef.h> /* size_t */

typedef struct Stack stack_t;

/* NULL pointers not allowed */
void STACKPop(stack_t *stack);

/* NULL pointers not allowed */
int STACKPush(stack_t *stack, const void *element);

/* NULL pointers not allowed */
void *STACKPeek(const stack_t *stack);

/* n_elements > 0, size_of_element > 0 */
stack_t *STACKCreate(size_t n_elements, size_t size_of_element);

/* NULL pointers not allowed */
size_t STACKSize(const stack_t *stack);

/* may not send same stack more than once */
void STACKDestroy(stack_t *stack);
