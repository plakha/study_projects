/*******************************************************************************
24/7/19 Knight Tour with/without heuristic
Author Andrei
Reviewer Sandra
*******************************************************************************/

#include <stdio.h> /* printf */
#include <time.h> /* time */
#include <assert.h> /* assert */
#include <stdlib.h> /* rand */

#include "barr.h" /* BARRIsOn */
#include "stack.h" /* stack_t */

#include "kt.h"

#ifndef TIME_OUT
#define TIME_OUT (180) /* limit execution of the function; default 180 sec */
#endif
#define N_SQUARES (64) /* standard chess table */
#define NO_MORE_MOVES (-1) /* denote end of legal moves */
#define SEC_PER_MIN (60.0)
enum {BAD_PATH = 3}; /* additional status, not present in API enum status */

typedef size_t chess_table_t; /* chess table represented as Bit Array */

/* "Static" modification Warnsdorff's heuristic: 
moves organized by degree - lesser to greater; 
changes in degrees in run-time are not tracked */
static const int g_move_table_heuristic[64][9] = {
						{10, 17, NO_MORE_MOVES}, 
						{16, 11, 18, NO_MORE_MOVES}, 
						{8, 12, 17, 19, NO_MORE_MOVES}, 
						{9, 13, 20, 18, NO_MORE_MOVES}, 
						{14, 10, 21, 19, NO_MORE_MOVES}, 
						{15, 11, 22, 20, NO_MORE_MOVES}, 
						{23, 12, 21, NO_MORE_MOVES}, 
						{22, 13, NO_MORE_MOVES}, 
						{2, 25, 18, NO_MORE_MOVES}, 
						{3, 24, 19, 26, NO_MORE_MOVES}, 
						{0, 4, 16, 25, 20, 27, NO_MORE_MOVES}, 
						{1, 5, 17, 21, 28, 26, NO_MORE_MOVES}, 
						{6, 2, 22, 29, 27, 18, NO_MORE_MOVES}, 
						{7, 23, 3, 30, 28, 19, NO_MORE_MOVES}, 
						{31, 4, 29, 20, NO_MORE_MOVES}, 
						{30, 21, 5, NO_MORE_MOVES}, 
						{1, 10, 33, 26, NO_MORE_MOVES}, 
						{0, 2, 32, 11, 27, 34, NO_MORE_MOVES}, 
						{8, 1, 3, 24, 12, 33, 28, 35, NO_MORE_MOVES}, 
						{4, 9, 2, 13, 25, 29, 36, 34, NO_MORE_MOVES}, 
						{5, 3, 14, 30, 10, 37, 35, 26, NO_MORE_MOVES}, 
						{6, 15, 31, 4, 38, 11, 36, 27, NO_MORE_MOVES}, 
						{7, 39, 5, 12, 37, 28, NO_MORE_MOVES}, 
						{6, 38, 13, 29, NO_MORE_MOVES}, 
						{9, 41, 18, 34, NO_MORE_MOVES}, 
						{8, 40, 10, 19, 35, 42, NO_MORE_MOVES}, 
						{9, 16, 32, 11, 41, 20, 36, 43, NO_MORE_MOVES}, 
						{12, 17, 33, 10, 21, 37, 44, 42, NO_MORE_MOVES}, 
						{13, 22, 11, 38, 45, 43, 34, 18, NO_MORE_MOVES}, 
						{14, 23, 39, 46, 12, 44, 35, 19, NO_MORE_MOVES}, 
						{15, 47, 13, 45, 36, 20, NO_MORE_MOVES}, 
						{14, 46, 37, 21, NO_MORE_MOVES}, 
						{49, 17, 26, 42, NO_MORE_MOVES}, 
						{48, 16, 50, 27, 18, 43, NO_MORE_MOVES}, 
						{49, 24, 40, 51, 17, 44, 28, 19, NO_MORE_MOVES}, 
						{52, 50, 41, 25, 18, 29, 45, 20, NO_MORE_MOVES}, 
						{30, 46, 53, 51, 21, 19, 26, 42, NO_MORE_MOVES}, 
						{31, 54, 47, 22, 52, 43, 27, 20, NO_MORE_MOVES}, 
						{55, 23, 53, 21, 28, 44, NO_MORE_MOVES}, 
						{54, 22, 29, 45, NO_MORE_MOVES}, 
						{57, 25, 50, 34, NO_MORE_MOVES}, 
						{56, 58, 24, 51, 26, 35, NO_MORE_MOVES}, 
						{57, 48, 32, 59, 52, 25, 36, 27, NO_MORE_MOVES}, 
						{60, 58, 49, 53, 33, 26, 37, 28, NO_MORE_MOVES}, 
						{54, 61, 59, 38, 50, 27, 34, 29, NO_MORE_MOVES}, 
						{55, 62, 39, 60, 30, 51, 35, 28, NO_MORE_MOVES}, 
						{63, 31, 61, 52, 36, 29, NO_MORE_MOVES}, 
						{62, 53, 30, 37, NO_MORE_MOVES}, 
						{58, 33, 42, NO_MORE_MOVES}, 
						{59, 32, 43, 34, NO_MORE_MOVES}, 
						{56, 60, 40, 33, 35, 44, NO_MORE_MOVES}, 
						{57, 61, 41, 34, 36, 45, NO_MORE_MOVES}, 
						{62, 58, 46, 35, 42, 37, NO_MORE_MOVES}, 
						{63, 59, 47, 38, 43, 36, NO_MORE_MOVES}, 
						{39, 60, 37, 44, NO_MORE_MOVES}, 
						{61, 38, 45, NO_MORE_MOVES}, 
						{41, 50, NO_MORE_MOVES}, 
						{40, 51, 42, NO_MORE_MOVES}, 
						{48, 52, 41, 43, NO_MORE_MOVES}, 
						{49, 53, 42, 44, NO_MORE_MOVES}, 
						{54, 50, 43, 45, NO_MORE_MOVES}, 
						{55, 46, 51, 44, NO_MORE_MOVES}, 
						{47, 52, 45, NO_MORE_MOVES}, 
						{53, 46, NO_MORE_MOVES}
												};
		

/* Moves organized Clock-wise from north-north-east - primitive table */
static const int g_move_table_no_heuristic[64][9] = {
						{10, 17, NO_MORE_MOVES}, 
						{11, 18, 16, NO_MORE_MOVES}, 
						{12, 19, 17, 8, NO_MORE_MOVES}, 
						{13, 20, 18, 9, NO_MORE_MOVES}, 
						{14, 21, 19, 10, NO_MORE_MOVES}, 
						{15, 22, 20, 11, NO_MORE_MOVES}, 
						{23, 21, 12, NO_MORE_MOVES}, 
						{22, 13, NO_MORE_MOVES}, 
						{2, 18, 25, NO_MORE_MOVES}, 
						{3, 19, 26, 24, NO_MORE_MOVES}, 
						{4, 20, 27, 25, 16, 0, NO_MORE_MOVES}, 
						{5, 21, 28, 26, 17, 1, NO_MORE_MOVES}, 
						{6, 22, 29, 27, 18, 2, NO_MORE_MOVES}, 
						{7, 23, 30, 28, 19, 3, NO_MORE_MOVES}, 
						{31, 29, 20, 4, NO_MORE_MOVES}, 
						{30, 21, 5, NO_MORE_MOVES}, 
						{1, 10, 26, 33,  NO_MORE_MOVES}, 
						{2, 11, 27, 34, 32, 0, NO_MORE_MOVES}, 
						{3, 12, 28, 35, 33, 24, 8, 1, NO_MORE_MOVES}, 
						{4, 13, 29, 36, 34, 25, 9, 2, NO_MORE_MOVES}, 
						{5, 14, 30, 37, 35, 26, 10, 3, NO_MORE_MOVES}, 
						{6, 15, 31, 38, 36, 27, 11, 4, NO_MORE_MOVES}, 
						{7, 39, 37, 28, 12, 5, NO_MORE_MOVES}, 
						{38, 29, 13, 6, NO_MORE_MOVES}, 
						{9, 18, 34, 41, NO_MORE_MOVES}, 
						{10, 19, 35, 42, 40, 8, NO_MORE_MOVES}, 
						{11, 20, 36, 43, 41, 32, 16, 9, NO_MORE_MOVES}, 
						{12, 21, 37, 44, 42, 33, 17, 10, NO_MORE_MOVES}, 
						{13, 22, 38, 45, 43, 34, 18, 11, NO_MORE_MOVES}, 
						{14, 23, 39, 46, 44, 35, 19, 12, NO_MORE_MOVES}, 
						{15, 47, 45, 36, 20, 13, NO_MORE_MOVES}, 
						{46, 37, 21, 14, NO_MORE_MOVES}, 
						{17, 26, 42, 49, NO_MORE_MOVES}, 
						{18, 27, 43, 50, 48, 16, NO_MORE_MOVES}, 
						{19, 28, 44, 51, 49, 40, 24, 17, NO_MORE_MOVES}, 
						{20, 29, 45, 52, 50, 41, 25, 18, NO_MORE_MOVES}, 
						{21, 30, 46, 53, 51, 42, 26, 19, NO_MORE_MOVES}, 
						{22, 31, 47, 54, 52, 43, 27, 20, NO_MORE_MOVES}, 
						{23, 55, 53, 44, 28, 21, NO_MORE_MOVES}, 
						{54, 45, 29, 22, NO_MORE_MOVES}, 
						{25, 34, 50, 57, NO_MORE_MOVES}, 
						{26, 35, 51, 58, 56, 24, NO_MORE_MOVES}, 
						{27, 36, 52, 59, 57, 48, 32, 25, NO_MORE_MOVES}, 
						{28, 37, 53, 60, 58, 49, 33, 26, NO_MORE_MOVES}, 
						{29, 38, 54, 61, 59, 50, 34, 27, NO_MORE_MOVES}, 
						{30, 39, 55, 62, 60, 51, 35, 28, NO_MORE_MOVES}, 
						{31, 63, 61, 52, 36, 29, NO_MORE_MOVES}, 
						{62, 53, 37, 30, NO_MORE_MOVES}, 
						{33, 42, 58, NO_MORE_MOVES}, 
						{34, 43, 59, 32, NO_MORE_MOVES}, 
						{35, 44, 60, 56, 40, 33, NO_MORE_MOVES}, 
						{36, 45, 61, 57, 41, 34, NO_MORE_MOVES}, 
						{37, 46, 62, 58, 42, 35, NO_MORE_MOVES}, 
						{38, 47, 63, 59, 43, 36, NO_MORE_MOVES}, 
						{39, 60, 44, 37, NO_MORE_MOVES}, 
						{61, 45, 38, NO_MORE_MOVES}, 
						{41, 50, NO_MORE_MOVES}, 
						{42, 51, 40, NO_MORE_MOVES}, 
						{43, 52, 48, 41, NO_MORE_MOVES}, 
						{44, 53, 49, 42, NO_MORE_MOVES}, 
						{45, 54, 50, 43, NO_MORE_MOVES}, 
						{46, 55, 51, 44, NO_MORE_MOVES}, 
						{47, 52, 45, NO_MORE_MOVES}, 
						{53, 46, NO_MORE_MOVES}
													};

#ifndef g_move_table
#define g_move_table (g_move_table_heuristic) /* by default, 
choose the heuristic table */
#endif

static void MoveStackToArray(int arr[], stack_t *stack)
{
	int i = N_SQUARES -1;

	assert(N_SQUARES == STACKSize(stack));

	while(0 != STACKSize(stack))
	{
		arr[i] = *(int *)STACKPeek(stack);
		--i;
		STACKPop(stack);
	}

	assert(0 == STACKSize(stack));		
}

static int IsFullTable(chess_table_t chess_table)
{
	return -1LU == chess_table; /* all bits set to 1 */
}

static int IsOccupiedSquare(chess_table_t chess_table, int current_move)
{
	return BARRIsOn(chess_table, current_move);
}

static chess_table_t SetOccupiedSquare(chess_table_t chess_table, 
									int current_move)
{
	return BARRSetOn(chess_table, current_move);
}

static chess_table_t SetFreeSquare(chess_table_t chess_table, 
								int current_move)									
{
	return BARRSetOff(chess_table, current_move);
}

static enum status UtilKT(stack_t *path, int current_move, 
						chess_table_t chess_table, const time_t start_time)
{
	int next_move = NO_MORE_MOVES;
	int i = 0;
	enum status ret_val = BAD_PATH;
	
	if (TIME_OUT < (time(NULL) - start_time))
	{
		return T_FAIL;
	}
	
	if (IsOccupiedSquare(chess_table, current_move))
	{
		return BAD_PATH;
	}
	
	chess_table = SetOccupiedSquare(chess_table, current_move);
	STACKPush(path, &current_move);
	
	if (IsFullTable(chess_table))
	{
		return OK;
	}
	
	for(; 
		NO_MORE_MOVES != (next_move = g_move_table[current_move][i]); 
		++i)
	{
		ret_val = UtilKT(path, next_move, chess_table, start_time);
		if (OK == ret_val)
		{
			return ret_val;
		}
	}
	
	chess_table = SetFreeSquare(chess_table, current_move);
	STACKPop(path);

	return ret_val;
}

enum status KT(int *path_ret, int first_move)
{
	stack_t *path = NULL;
	chess_table_t chess_table = 0;
	enum status ret_val = OK;
	time_t start_time = -1;
	
	assert(path_ret);
	assert(0 <= first_move);
	assert(N_SQUARES > first_move);

	path = STACKCreate(N_SQUARES, sizeof(int));
	if (!path)
	{
		return M_FAIL;
	}

	start_time = time(NULL);
	
	ret_val = UtilKT(path, first_move, chess_table, start_time);
	
	if (OK == ret_val)
	{
		assert(N_SQUARES == STACKSize(path));
		MoveStackToArray(path_ret, path);
	} 
	
	STACKDestroy(path);
	path = NULL;

	return ret_val;
}

static int ValidatePath(const int arr[])
{
	int i = 0, j = 0;

	for (; i < N_SQUARES; ++i)
	{
		if (0 > arr[i] || N_SQUARES <= arr[i])
		{
			return BAD_PATH;
		}
		for (j =1 + i; N_SQUARES > j; ++j)
		{
			if (arr[i] == arr[j])
			{
				return BAD_PATH;
			}
		}
	}

	return OK;
}

int main()
{
	int path[N_SQUARES] = {0};
	int i = 0;
	int ret_val = OK;
	int first_move = 36;
	
	srand(clock());
/*	first_move = rand() % N_SQUARES;*/

	puts("This program calculates and prints a Knight's tour\
		 starting from a random square\n\n..working..\n");
	
	ret_val = KT(path, first_move);
	switch (ret_val)
	{
		case OK:
			puts("Found a route");
			break ;
		case T_FAIL:
			printf("Quitting after set timeout of %0.2f min", 
				TIME_OUT/SEC_PER_MIN);
			break ;
		case M_FAIL:
			puts("Memory allocation failure - free your resources");
			break ;
		case BAD_PATH:
			puts("A solution is not in existence");
			break ;
	}
	
	if (BAD_PATH == ValidatePath(path))
	{
		printf("The calculation failed.\
			 Please contact the developer with the code %d", first_move);	
	}

	printf("Found route.\nStart of route-> ");
	for (i = 0; OK == ret_val && i < 64; ++i)
	{
		printf("%d-> ", path[i]);
	}
	puts("end of route");

	return ret_val;
}
