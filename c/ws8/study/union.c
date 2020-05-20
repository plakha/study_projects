union numbers
{
	int i;
	float f;
};

int main()
{
	union numbers a = {.f = 1.4};
	printf ("%d %f ", a.i, a.f);


}
