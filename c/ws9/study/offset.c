typedef struct {
	float x;
	float y;
}point_type;

typedef struct
{
	point_type *coordinates;
	unsigned int population;
}city_type;

#define OFFSET(s, f)\
	&(((s *)0)->f)

int main()
{
	point_type grinwich_coord = {0, 15};
	city_type grinwich;
	*(grinwich.coordinates) = grinwich_coord;
	grinwich.population = 500000;
	
	printf("%lu\n", OFFSET(city_type, population));
	return 0;
}
