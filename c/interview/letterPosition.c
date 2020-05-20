#include <stdio.h>  /* sprintf() */
#include <string.h> /* strlen() */
#include <stdlib.h> /* calloc() */
#include <assert.h> /* assert */

#define ILLEGAL_CHAR_POS (-1)

static int letterPosition(char letter)
{
  if ('A' <= letter && 'Z' >= letter)
  {
    return (int)(letter - 'A' + 1);
  }

  if ('a' <= letter && 'z' >= letter)
  {
    return (int)(letter - 'a' + 1);
  }

  return ILLEGAL_CHAR_POS;
}

char *alphabet_position(char *text)
{
  char *buffer = calloc(2 * strlen(text), sizeof(*buffer));

  for (size_t i = 0; '\0' != text[i]; ++i)
  {
    int letter_position = ILLEGAL_CHAR_POS;
    if (ILLEGAL_CHAR_POS != (letter_position = letterPosition(text[i])))
    {
      sprintf(buffer + strlen(buffer), "%d ", letter_position); //append the next letter position
    }
  }

  puts(buffer);

  buffer[strlen(buffer) - 1] = '\0';

  return buffer;
}

static size_t nDigits(int n)
{
  assert(0 != n);

  size_t nDigits = 0;

  while (0 != n)
  {
    ++nDigits;
    n /= 10;
  }

  return nDigits;
}

int main()
{
  printf("%lu\n", nDigits(-10));
}





// char *alphabet_position(char *text)
// {
//   char *buffer = malloc(2 * strlen(text) * sizeof(*buffer));
//   size_t buffer_pos = 0;

//   buffer[0] = '\0'; //in case buffer will return empty to the caller

//   for (size_t i = 0; '\0' != text[i]; ++i)
//   {
//     int letter_position = ILLEGAL_CHAR_POS;

//     if (ILLEGAL_CHAR_POS != (letter_position = letterPosition(text[i])))
//     {
//       sprintf(buffer + buffer_pos, "%d ", letter_position); //append the next letter alphabet-position and space
//     }

//     buffer_pos += 1 + nDigits(letter_position); //space takes one position
//   }

//   if (0 < buffer_pos)
//   {
//     //assert('\0' != buffer[0]); /* this assertion means, the buffer has been filled at least once. Sometimes it fails for a buffer that has been filled. Don't know why */
//     buffer[buffer_pos - 1] = '\0'; //put terminating null instead of the last space
//   }

//   return buffer;
// }

