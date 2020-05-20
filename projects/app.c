/* compile with gcc because of signals 
gcc -o app watchdog.c app.c 
*/

#include <stdio.h> /* printf() */
#include <limits.h> /* INT_MAX */
#include <signal.h> /* struct sigaction */
#include <unistd.h> /* sleep() */

#include "watchdog.h"

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m\x1b[1m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

#define WD_ID (1) 

void MyFunc()
{
    int i = 0;
    
    for (; 20 > i; ++i)
    {
/*        printf("%d My little china girl\n", i);*/
        sleep(2);
    }
}

int main(int argc, char *argv[])
{
    int status = 0;
        
    status = WDStart(argc, argv, WD_ID);
    MyFunc();

    puts(RED"Stopping WATCHDOG"RESET);
    WDStop();
    
    return status;
}
