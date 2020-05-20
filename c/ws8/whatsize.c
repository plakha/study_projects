union numbers
{
	int i; //4B
	float f; //4B
	double d; //8B
};//16B

struct x
{
	int i; //4B
	char c; //1 B
	//char pad[3]
	double d;//8B
	short s;//2B
	//char pad[6]
};//24B

struct card
{
	unsigned int suit : 2; //2b
	unsigned int face_value : 4;//4b
	// pad 2b
	//char pad[3]
};//4B

int main()
{
	printf("%lu\n, %lu\n, %lu\n", sizeof(union numbers), sizeof(struct x), sizeof(struct card));
}
