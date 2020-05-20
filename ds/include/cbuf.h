/*cbuf may be useful in file descriptors. 
we will use errno! - be gentle - it touches the kernel
ENODATA - when buffer has no data
EOVERFLOW - when buffer is full

cant overwrite data that ios not read yet

*/

/* struct CBUF
{
    size_t capacity;
    size_t size;
    size_t read_offset;
    void *buff;
}*/
#include <stddef.h> /* size_t */

/* typedef struct CBUF cbuf_t; */
typedef struct CBUF cbuf_t;

/* No zero as input. */
cbuf_t *CBUFCreate(size_t nbytes);

/* No null pointer as input. */
void CBUFDestroy(cbuf_t *cbuf);

/* return how many bytes written, if buffer full set errno EOVERFLOW.
No null pointer as input. */
size_t CBUFWrite(cbuf_t *cbuf, const void *data, size_t nbytes);

/* No null pointer as input. */
size_t CBUFRead(cbuf_t *cbuf, void *data, size_t nbytes);

/* */
size_t CBUFCapacity(cbuf_t *cbuf);

/* (Boolean) return are all read/none written.
No null pointer as input. */
int CBUFIsEmpty(const cbuf_t *cbuf);

/* Return bytes available to write. 
No null pointer as input*/
size_t CBUFFreeSpace(cbuf_t *cbuf);
