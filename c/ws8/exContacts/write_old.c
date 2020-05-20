#include <stdio.h> /* fopen */
#include <errno.h> /* errno */
#include <stdlib.h> /* sizeof */

/**header******/
#define NUM_STUDENTS 10

typedef struct date_of_birth
{
	size_t day;
	size_t month;
	size_t year;
} date_of_birth_t;

typedef struct contact
{
	char f_name[50];
	char l_name[50];
	size_t id;
	struct date_of_birth dob;
} contact_type;

contact_type students[] = { {"Andy", "Warhol", 1, {1, 2, 1920}}, 
							{"Arik", "Einstein", 2, {25, 8, 1932}}, 
							{"Napoleon", "Third", 3, {9, 4, 1805}}, 
							{"Napoleon", "Dynamite", 4, {8, 1, 1985}}, 
							{"Bee", "Jee", 5, {5, 3, 1970}}, 
							{"Sting", "Ray", 6, {7, 5, 1958}}, 
							{"Tom", "Riddle", 7, {7, 4, 1945}}, 
							{"Harry", "Potter", 8, {8, 8, 1991}}, 
							{"Josephus", "Flavius", 9, {8, 8, 8}}, 
							{"Napoleon", "First", 10, {30, 5, 1760}} };

char filename[] = "student_list";
/********end header************/

int main()
{
	FILE *file = NULL;
	contact_type *students_copy = NULL;

	file = fopen(filename, "w");
	if(NULL == file)
	{
		printf("%s", strerror(errno));
		
		return 1;
	}

	puts(students[1].f_name);
	
	if(NUM_STUDENTS > fwrite(students, sizeof(*students), NUM_STUDENTS, file))
	{
		printf("%s", strerror(errno));
		
		return 1;
	}

	students_copy = (contact_type *)malloc(NUM_STUDENTS * sizeof(*students_copy));
	
	if(0 != fclose(file))
	{
		printf("%s", strerror(errno));
		
		return 1;
	}
	
	file = fopen(filename, "r");
	if(NULL == file)
	{
		printf("%s", strerror(errno));
		
		return 1;
	}
	fread(students_copy, sizeof(*students_copy), NUM_STUDENTS, file);
	if(0 != fclose(file))
	{
		printf("%s", strerror(errno));
		
		return 1;
	}

	

	puts(students_copy[1].f_name);

	free(students_copy);	
	
	return 0;
}

static PrepareStream();
static CopyPasteFromStream();
static CloseStream();
