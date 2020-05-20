int g1;
static int g2;
static int g3 = 0;
static int g4 = 8;

static void fool()
{
	static int g5;
	int l1 = 9;
}

void foo()
{
	static int g6;
	static int g7;
}

extern void bar()
{
	--g2;
}
