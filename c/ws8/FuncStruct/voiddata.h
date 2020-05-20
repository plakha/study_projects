typedef struct item
{
	void *data;
	void (*add)(void **data, int num);
	void (*print)(const void *data);
	void (*free)(void **data);
} item_t;

void AddToInt(void **data, int num);
void PrintInt(const void *data);

void AddToFloat(void **data, int num);
void PrintFloat(const void *data);

void AddToStr(void **data, int num);
void PrintStr(const void *data);

void ResetToZero(void ** data);
void FreeStr(void **data);


