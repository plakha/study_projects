/*******************************************************************************
The implementation of bitarray is functional (no side effects). Bit array 
is represented by unsigned long. Index is counted from the right to left.
*******************************************************************************/

#include <stddef.h> /* size_t */

/* Return Bit Array with bit on given index set to given value ( 0 or 1 only). 
Index expected 0 - 63. */
size_t BARRSetBit(size_t arr, int index, int value);

/* Return Bit Array with bit on given index set to 1. Index expected 0 - 63. */
size_t BARRSetOn(size_t arr, int index);

/* Return Bit Array with bit on given index set to 0.Index 
expected 0 - 63. */
size_t BARRSetOff(size_t arr, int index);

/* Return Bit Array with bit on given index flipped.Index expected 0 - 63. */
size_t BARRFlip(size_t arr, int index);

/* Return Bit Array with bits mirrored. E.g. given "10011", return "11001" */
size_t BARRMirror(size_t arr);

/* Check if bit with given index is on. Index expected 0 - 63. */
int BARRIsOn(size_t arr, int index);

/* Check if bit with given index is off. Index 
expected 0 - 63. */
int BARRIsOff(size_t arr, int index);

/* Rotate Bit Array left by "amount" times. E.g. given Bit Array "1000",
amount 3, return "0100 */
size_t BARRRotateLeft(size_t arr, size_t amount);

/* Rotate Bit Array right by "amount" times. E.g. given Bit Array "1000",
amount 3, return "0001" */
size_t BARRRotateRight(size_t arr, size_t amount);

/* Return number of bits set to 1 */
size_t BARRCountOn(size_t arr);

/* Return number of bits set to 0 */
size_t BARRCountOff(size_t arr); 

 
/* Return Bit Array with bits mirrored. E.g. given "10011", return "11001". 
Employs on-demand LUT. Mind that execution may be slow on first call.
The function may allocate and not free memory. */
size_t BARRMirrorLUT(size_t arr);

/* Return number of bits set to 1. Employs on-demand LUT. Mind that 
execution may be slow on first call.
The function may allocate and not free memory. */
size_t BARRCountOnLUT(size_t arr);




