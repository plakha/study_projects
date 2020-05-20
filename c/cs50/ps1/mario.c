#include <stdio.h>  /* getchar() */
#include <ctype.h>  /* isdigit() */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert() */

static int GetInput()
{
  const int MIN_HEIGHT = 1;
  const int MAX_HEIGHT = 8;
  int input_height = 0;
  char *input_buf = malloc(100 * sizeof(*input_buf));

  while (MIN_HEIGHT > input_height || MAX_HEIGHT < input_height)
  {
    printf("Height:");
    if (NULL == fgets(input_buf, 100, stdin)) //got no input
    {
      continue;
    }

    input_height = atoi(input_buf);
  }

  free(input_buf);
  input_buf = NULL;

  return input_height;
}

static void BuildRow(int n_hash, int n_space)
{
  for (int i = 0; i < n_space; ++i)
  {
    putchar(' ');
  }

  for (int i = 0; i < n_hash; ++i)
  {
    putchar('#');
  }

  putchar(' ');
  putchar(' ');

  for (int i = 0; i < n_hash; ++i)
  {
    putchar('#');
  }

  puts("");
}

static void BuildPyramids(int rows)
{
  assert(rows > 0);

  int n_hash = 1;
  int n_space = rows - n_hash;

  while (n_hash <= rows)
  {
    BuildRow(n_hash, n_space);
    ++n_hash;
    --n_space;
  }
}

int main()
{

  BuildPyramids(GetInput());
  return 0;
}
