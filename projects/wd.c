/*
    Watchdog 21/8/2019
    Source code for prog to put in the Client's directory 
*/

#include <unistd.h> /* sleep() */
#include <limits.h> /* INT_MAX */
#include <stdio.h> /* printf() */

#include <stdlib.h> /* exit() */
#include <pthread.h> /* pthread_t */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* getpid() */
#include <signal.h> /* sigaction() */
#include <errno.h> /* errno */
#include <sys/sem.h> /* semop() */
#include <assert.h> /* assert() */
#include <string.h> /* strerror() */
#include <sys/wait.h> /* waitpid() */

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m\x1b[1m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

#include "scheduler.h" /* *ScdCreate() */
#include "uid.h" /* UIDCreate() */

#include "watchdog.h" /* error codes */

#define APP_READY_SEM (0)
#define WD_READY_SEM (1)
#define N_SEM (2)
#define HEARTBEAT_INTERVAL (1)
#define CHECK_ALIVE_INTERVAL (3)
#define KEEP_TASK (0)
#define REMOVE_TASK (-1)
#define FALSE (0)
#define STDOUT (1)

static const char *signal_error_message = "Watchdog error 1.\
                                           Please contact the developer.";
static const char *scheduler_error_message = "Watchdog error 2.\
                                              Please contact the developer.";
static const char *sem_error_message = "Watchdog error 3.\
                                        Please contact the developer.";

static volatile sig_atomic_t g_is_app_alive = 1;
static volatile sig_atomic_t g_should_stop = FALSE;
static pid_t g_app_pid = -1;
static int g_semid = -1;
static char **g_argv = NULL;
static struct sembuf g_op[N_SEM] = {{APP_READY_SEM, -1, 0},
                                    {WD_READY_SEM, 2, 0}};

static void SAHandlerSigUsr1(int sig)
{
    g_is_app_alive = 1;

    (void)sig;
}

static void SAHandlerSigUsr2(int sig)
{
    g_should_stop = 1;
    kill(g_app_pid, SIGUSR2);

    (void)sig;
}

static int InitSigAction()
{
    int status = 0;
    struct sigaction sa = {0};
        
    sa.sa_handler = &SAHandlerSigUsr1;    
    if (sigaction(SIGUSR1, &sa, NULL))
    {
        status = errno;

        return status;
    }  
    
    sa.sa_handler = &SAHandlerSigUsr2;    
    if (sigaction(SIGUSR2, &sa, NULL))
    {
        status = errno;
    }  
    
    return status;
}

static long CheckHeartBeat(void *params)
{ 
    if (g_should_stop)
    {
        return REMOVE_TASK;
    }
    
    kill(g_app_pid, SIGUSR1);
    
    (void)params;
    
    return KEEP_TASK;
}

static void Revive()
{   
    printf(MAGENTA"WD revives APP\n"RESET);
    
    waitpid(g_app_pid, NULL, 0);
    g_app_pid = fork();
    if (0 == g_app_pid)
    {
        if (-1 == execvp(g_argv[2], g_argv + 2))
        {
            assert(FALSE);
            exit(1);
        }
    }
    else 
    {
        if (-1 == semop(g_semid, g_op + APP_READY_SEM, 1LU))
        {
            perror(sem_error_message);
        } 
    }
}

static long CheckAlive(void *params)
{
    if (g_should_stop)
    {
        return REMOVE_TASK;
    }
    
    (void)params;
    
    if (!g_is_app_alive)
    {
        Revive();
    }

    g_is_app_alive = 0; /* app revived */
    
    return KEEP_TASK;
}

static scd_t *Schedule(scd_t *scheduler)
{
    unid_t task = bad_uid;

    scheduler = ScdCreate();
    if (!scheduler)
    {
        return NULL;
    }
    
    task = ScdAdd(scheduler, HEARTBEAT_INTERVAL, &CheckHeartBeat , NULL); 
    if (UIDIsBad(task))
    {        
        ScdDestroy(scheduler);
        scheduler = NULL;  

        return NULL;
    }

    task = ScdAdd(scheduler, CHECK_ALIVE_INTERVAL, &CheckAlive, NULL);
    if (UIDIsBad(task))
    {
        ScdDestroy(scheduler);
        scheduler = NULL;  
    }    
    
    return scheduler;    
}

static int Watchdog(char **argv)
{
    int status = 0;
    scd_t *scheduler = NULL;    
    
    assert(argv);

    g_app_pid = getppid();
    g_argv = argv;
    
    assert(argv[1]);
    g_semid = atoi(argv[1]);
    
    status = InitSigAction();
    if (status)
    {
        puts(signal_error_message);
        puts(strerror(status)); /* status contains errno */

        return WD_E_SIGACT;
    }
    
    scheduler = Schedule(scheduler);
    if (!scheduler)
    {
        puts(scheduler_error_message);

        return WD_E_MEM;
    }
    
    /* set WD ready */
    if (-1 == semop(g_semid, g_op + WD_READY_SEM, 1LU))
    {
        return WD_E_SEM; 
    }
   
   /* From here we'll be signalling to the app */
    ScdRun(scheduler);

    /* The app called WDStop() */
    ScdDestroy(scheduler);
    scheduler = NULL;
    
    return status;
}

int main(int argc, char *argv[])
{  
    assert(2 < argc);
       
    printf(CYAN"Watchdog running!\n"RESET);
    
    return Watchdog(argv);
}