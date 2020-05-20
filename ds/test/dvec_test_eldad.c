/*******************************************************************************
* Programmer: Eldad
* dvec
* File: dvec testing
* Date: 30-05-2019 18:08:19
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */

#include "../include/dvec.h" /* Dynamic Vector header */

/*Print Colors*****************************************************************/
#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"
/******************************************************************************/
static void TestDVEC(void);


int main(void)
{
    puts(CYAN"          Dynamic Vector:"RESET);
    puts(MAGENTA"-------------------------------------"RESET);
    
    TestDVEC();    

    puts(MAGENTA"-------------------------------------"RESET);
    
    return (EXIT_SUCCESS);
}

static void TestDVEC(void)
{
    int data = 71070;
    int i = 0;
    int failure_flag = 0;    
/* 01. Create */    
    dvec_t *dvec = DVECCreate(sizeof(int), 4);
    printf(YELLOW"01 . Create                 : "RESET);      
    puts((dvec) ? (GREEN"SUCCESS"RESET) : (RED"FAILURE"RESET));

/* 02. Get Size & Capacity @ Empty */    
    printf(YELLOW"02 . Size & capacity @ empty: "RESET);   
    puts(((0 == DVECSize(dvec)) && (4 == DVECCapacity(dvec)))
                                 ? (GREEN"SUCCESS"RESET) : (RED"FAILURE"RESET));

/* 03. Push 3, check size increase, push 1 more, check capacity increase */
    printf(YELLOW"03a. Push Loop w/o Resize   : "RESET);
    for (i = 0; i < 3; ++i)
    {
        if (1 == DVECPushBack(dvec, &i))
        {
            puts(RED"FAILURE @PUSH LOOP"RESET);
            failure_flag = 1;
            printf(YELLOW"03b. Push with realloc       : "RESET);                   
            puts(CYAN"SKIPPED DUE TO 3a FAILURE @LOOP"RESET);
            break;
        }
    }           
    
    if (0 == failure_flag)
    {
        puts(((3 == DVECSize(dvec)) && (4 == DVECCapacity(dvec))) 
                  ? (GREEN"SUCCESS"RESET) : (RED"FAILURE @SIZE&CAP TEST"RESET));

        printf(YELLOW"03b. Push with realloc      : "RESET);       
        DVECPushBack(dvec, &i);
        puts(((4 == DVECSize(dvec)) && (8 == DVECCapacity(dvec))) 
                   ? (GREEN"SUCCESS"RESET) : (RED"FAILURE @REALLOC TEST"RESET));              
    }
    
/* 04. Get Item Address */
        printf(YELLOW"04 . Get Item Address       : "RESET);           
        puts(((0 == *(int *)(DVECGetItemAddress(dvec, 0))) 
                                && (3 == *(int *)(DVECGetItemAddress(dvec, 3)))) 
                  ? (GREEN"SUCCESS"RESET) : (RED"FAILURE"RESET));

/* 05. Pop + Pop & Downsize */
        printf(YELLOW"05a. Pop Once               : "RESET);           
        DVECPopBack(dvec);
        puts(((3 == DVECSize(dvec)) && (8 == DVECCapacity(dvec))) 
                       ? (GREEN"SUCCESS"RESET) : (RED"FAILURE @FIRSTPOP"RESET)); 
        printf(YELLOW"05b. Pop with Resize        : "RESET);
        DVECPopBack(dvec);
        puts(((2 == DVECSize(dvec)) && (4 == DVECCapacity(dvec))) 
               ? (GREEN"SUCCESS"RESET) : (RED"FAILURE @REALLOC DOWNSIZE"RESET));

/* 06. Reserve */
        printf(YELLOW"06a. Reserve 1024 slots     : "RESET);                  
        DVECReserve(dvec, 1024);
        puts(((2 == DVECSize(dvec)) && (1024 == DVECCapacity(dvec))) 
                                 ? (GREEN"SUCCESS"RESET) : (RED"FAILURE"RESET));
        
        printf(YELLOW"06b. Push one check capacity: "RESET);                          
        DVECPushBack(dvec, &data);
        puts(((3 == DVECSize(dvec)) && (1024 == DVECCapacity(dvec))) 
                                 ? (GREEN"SUCCESS"RESET) : (RED"FAILURE"RESET));
        
        printf(YELLOW"06c. Pop one check capacity : "RESET);                          
        DVECPopBack(dvec);
        puts(((2 == DVECSize(dvec)) && (512 == DVECCapacity(dvec))) 
                                 ? (GREEN"SUCCESS"RESET) : (RED"FAILURE"RESET));

        printf(YELLOW"06d. Four pushes one pop    : "RESET);                                  
        DVECPushBack(dvec, &data);                                 
        DVECPushBack(dvec, &data);                                         
        DVECPushBack(dvec, &data);                                 
        DVECPushBack(dvec, &data);                                         
        DVECPopBack(dvec);
        puts(((5 == DVECSize(dvec)) && (256 == DVECCapacity(dvec))) 
                                 ? (GREEN"SUCCESS"RESET) : (RED"FAILURE"RESET));
           
        printf(YELLOW"06d. Reserve to smaller     : "RESET);                          
        DVECReserve(dvec, 4);
        DVECReserve(dvec, 0);
        puts(((5 == DVECSize(dvec)) && (6 == DVECCapacity(dvec))) 
                                 ? (GREEN"SUCCESS"RESET) : (RED"FAILURE"RESET));                                                   
        
        DVECDestroy(dvec);
}




#if 0  



        printf("%ld, %ld\n", DVECSize(dvec), DVECCapacity(dvec)); 

    printf("%d, %d\n", *(int *)(DVECGetItemAddress(dvec, 0)), *(int *)(DVECGetItemAddress(dvec, 3)));
    printf("%p, %p\n", (DVECGetItemAddress(dvec, 0)), (DVECGetItemAddress(dvec, 2)));  
#endif 



