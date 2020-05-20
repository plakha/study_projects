#include <stdio.h> /* puts() */
#include <stdlib.h> /* atoll() */
#include <string.h> /* strncmp() */

static size_t SumOfDigits(size_t num)
{
  size_t sum_of_digits = 0;

  while (0 != num)
  {
    sum_of_digits += num % 10;
    num /= 10;
  }

  return sum_of_digits;
}

/* sum of digits of every other digit time 2 */
static size_t EveryOtherDigitMult2Sum(size_t card_num)
{
  size_t sum = 0;
  card_num /= 10; /* start with second-to-last digit */

  while (0 != card_num)
  {
    sum += SumOfDigits((card_num % 10) * 2);
    card_num /= 100; /* get next other digit on the next iteration */
  }

  return sum;
}

static size_t SumUnmultDigits(size_t card_num)
{
  size_t sum = 0;

  while (0 != card_num)
  {
    sum += card_num % 10;
    card_num /= 100;
  }

  return sum;
}

static int IsLuhnValid(size_t card_num)
{
  return 0 == (SumUnmultDigits(card_num) + EveryOtherDigitMult2Sum(card_num)) % 10;
}
/*
.All American Express numbers start with 34 or 37; 
most MasterCard numbers start with 51, 52, 53, 54, or 55 (they also have some other potential starting numbers which we won’t concern ourselves with for this problem);
and all Visa numbers start with 4.
*/

static const char *AMERICAN_EXPRESS_PREFIXES[] = {"34", "37", NULL};
static const char *VISA_PREFIXES[] = {"4", NULL};
static const char *MASTER_CARD_PREFIXES[] = {"51", "52", "53", "54", "55", NULL};


static const char *AMERICAN_EXPRESS = "AMEX\n";
static const char *MASTER_CARD = "MASTERCARD\n";
static const char *VISA = "VISA\n";
static const char *INVALID = "INVALID\n";

static int StartsWithAPrefix(const char *card_num, const char *prefixes[], size_t size_of_a_prefix)
{
  for (int i = 0; NULL != prefixes[i]; ++i)
  {
    if (0 != strncmp(card_num, prefixes[i], size_of_a_prefix))
    {
      return 0;
    }
  }

  return 1;
}

const char *WhichCard(size_t card_num)
{
  const char *output = NULL;
  char *card_num_str = NULL;

  if (!IsLuhnValid(card_num))
  {
    return INVALID;
  }

  card_num_str = malloc(20 * sizeof(*card_num_str));
  if (NULL == card_num_str)
  {
    return NULL;
  }
  sprintf(card_num_str, "%lu", card_num);

  if (StartsWithAPrefix(card_num_str, AMERICAN_EXPRESS_PREFIXES, strlen(AMERICAN_EXPRESS_PREFIXES[0])))
  {
    output = AMERICAN_EXPRESS;
  }
  else if (StartsWithAPrefix(card_num_str, VISA_PREFIXES, strlen(VISA_PREFIXES[0])))
  {
    output = VISA;
  }
  else if(StartsWithAPrefix(card_num_str, MASTER_CARD_PREFIXES, strlen(MASTER_CARD_PREFIXES[0])))
  {
    output = MASTER_CARD;
  }

  free(card_num_str);
  card_num_str = NULL;

  return output;
}

int main()
{
  
}