extern const unsigned char lut[];



int main()
{
int n = 256;
int i = 0;
for (i = 1; i < n; ++i)
  
  printf ("%d ", lut[i]);
}
