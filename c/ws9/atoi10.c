/*static void Swap(char *c1, char *c2)
{
	char hold = *c1;
	*c1 = *c2;
	*c2 = hold;
}

static char *InvertStr(char *left, char *right)
{
	char *run_left = left;
	char *run_right = right;
	
	while(run_left < run_right)
	{
	Swap(run_left, run_right);
	++run_left;
	--run_right;
	}

	return left;
}

int AtoI10(char *a, unsigned int i)
{
	char *run = a;

	while(i > 0)
	{
		*run = (i % 10) + '0' ;
		i /= 10; 
		++run;
	}
	*run = '\0';
	
	return InvertStr(a, run - 1);
}
*/
