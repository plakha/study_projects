/*
    21/8/2019
    Final C Project: Watchdog
    By: Andrei
    Reviewer: Sandra
*/

#include <limits.h> /* INT_MAX */
#include <stdio.h> /* printf() */
#include <errno.h> /* errno */

#include <stdlib.h> /* exit() */
#include <pthread.h> /* pthread_t */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* getpid() */
#include <signal.h> /* sigaction() */
#include <string.h> /* memset() */
#include <unistd.h> /* sleep() */
#include <pthread.h> /* pthread_t */
#include <assert.h> /* assert() */
#include <sys/sem.h> /* semop() */
#include <sys/ipc.h> /* ftok() */
#include <sys/wait.h> /* waitpid() */

#include "scheduler.h" /* *ScdCreate() */
#include "uid.h" /* UIDCreate() */

#include "watchdog.h"

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m\x1b[1m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

#ifndef WD_PATH
#define WD_PATH ("./wd.out") 
#endif /* WD_PATH */

#define LEN_OF_MAX_INT (12) /* 10 digits, plus '-', the terminating null */
#define HEARTBEAT_INTERVAL (1)
#define CHECK_ALIVE_INTERVAL (3)
#define SEM_FLAG (0600) /* the user may read and alter the semaphore */
#define N_SEM (2) /* 2 semaphores: controlling the app and the puppy */
#define APP_READY_SEM (0)
#define WD_READY_SEM (1)
#define KEEP_TASK (0)
#define REMOVE_TASK (-1);
#define FALSE (0)

static const char *exec_error_message = 
                    "WDStart() couldn't run wd.out: \
                     either put wd.out in the same directory as your app,\
                     or compile your app with the flag -DWD_PATH=\"...\"\
                     where \"...\" is the directory where you put wd.out\n";

static volatile sig_atomic_t g_is_wd_alive = 1;
static volatile sig_atomic_t g_should_tasks_stop = FALSE;
static volatile sig_atomic_t g_confirmed_wd_to_die = FALSE;
static pid_t g_wd_pid = -1;
static char **g_argv = NULL;
static int g_semid = -1;
static pthread_t g_watch_thread_id;
static struct sembuf g_op[N_SEM] = {{APP_READY_SEM, 1, 0},
                                    {WD_READY_SEM, -1, 0}};
                                  
static void SAHandlerSigUsr1(int sig)
{
    g_is_wd_alive = 1;
   
    (void)sig;
}

static void SAHandlerSigUsr2(int sig)
{
    g_confirmed_wd_to_die = 1;

    (void)sig;
}

static void *ThrWatchRoutine(void *args)
{
    scd_t *scheduler = (scd_t *)args;
    
    ScdRun(scheduler);
    
    ScdDestroy(scheduler);
    scheduler = NULL;
    
    return args;
}

static int InitAppWatch(scd_t *scheduler)
{
    /* Here be open a thread signalling to the watchdog */      
    assert(scheduler);
    
    memset(&g_watch_thread_id, 0, sizeof(g_watch_thread_id));
    
    if (pthread_create(&g_watch_thread_id, NULL, 
                       ThrWatchRoutine, (void *)scheduler))
    {
        puts("Couldn't init watch thread in user app");
        
        return WD_E_THREAD;
    }
    
    return WD_OK;
}

static long CheckHeartBeat(void *params)
{ 
    if (0 != g_should_tasks_stop)
    {
        return REMOVE_TASK;
    }
    
    kill(g_wd_pid, SIGUSR1);
    
    (void)params;
    
    return KEEP_TASK;  
}

static int InitSigAction()
{
    int status = 0;
    struct sigaction sa;
    
    memset(&sa, 0, sizeof(sa));
    
    sa.sa_handler = &SAHandlerSigUsr1;    
    if (sigaction(SIGUSR1, &sa, NULL))
    {
        status = errno;
    }  
    
    sa.sa_handler = &SAHandlerSigUsr2;    
    if (sigaction(SIGUSR2, &sa, NULL))
    {
        status = errno;
    }
    
    return status;
}

#define OFFSET_G_ARGC (2)
static int InitGArggv(int user_argc, char **user_argv, int sem_id )
{
    char *sem_id_str = NULL;
    int i = 0;
    
    sem_id_str = malloc(sizeof(*sem_id_str) * LEN_OF_MAX_INT);
    if (!sem_id_str)
    {
        return WD_E_MEM;
    }
    if(0 >= sprintf(sem_id_str, "%d", sem_id))
    {
        free(sem_id_str);
        sem_id_str = NULL;
        
        return WD_E_MEM;   
    }
    
    g_argv = malloc(sizeof(g_argv) * (user_argc + 3));
    if (!g_argv)
    {
        free(sem_id_str);
        sem_id_str = NULL;
        
        return WD_E_MEM;   
    }
    
    g_argv[0] = WD_PATH;
    g_argv[1] = sem_id_str;
    
    for (i = 0; i < user_argc; ++i)
    {
        g_argv[i + OFFSET_G_ARGC] = user_argv[i];
    }
    g_argv[OFFSET_G_ARGC + user_argc] = NULL; /* terminating null */
    
    return 0;
}
#undef OFFSET_G_ARGC

static void DestroyGArgv()
{
    char *sem_id_str = g_argv[1];

    free(sem_id_str);
    sem_id_str = NULL;

    free(g_argv);
    g_argv = NULL;
}

static void Revive()
{   
    printf(CYAN"App revives WD\n"RESET);
    
    waitpid(g_wd_pid, NULL, 0);
    
    if (-1 == semop(g_semid, g_op + WD_READY_SEM, 1LU))
    {
        perror("app couldn't op the wd semaphore");
    }   

    g_wd_pid = fork();
    if (0 == g_wd_pid)
    {
        if (-1 == execvp(g_argv[0], g_argv))
        {
            puts(exec_error_message);
            exit(1);
        }
    }
    else 
    {    
        if (-1 == semop(g_semid, g_op + WD_READY_SEM, 1LU))
        {
            perror("app couldn't op the wd semaphore");
        } 
    }
}

static long CheckAlive(void *params)
{
    (void)params;
    
    if (0 != g_should_tasks_stop)
    {
        return REMOVE_TASK;
    }
    
    if(!g_is_wd_alive)
    {
        Revive();
    }
    
    g_is_wd_alive = FALSE;
    
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
    
    task = ScdAdd(scheduler, HEARTBEAT_INTERVAL, CheckHeartBeat , NULL); 
    if (UIDIsBad(task))
    {
        ScdDestroy(scheduler);
        scheduler = NULL;

        return NULL;
    }
    
    task = ScdAdd(scheduler, CHECK_ALIVE_INTERVAL, CheckAlive, NULL);
    if (UIDIsBad(task))
    {
        ScdDestroy(scheduler);
        scheduler = NULL;
    }
    
    return scheduler;
}

static int CreateSemaphore(int proj_id)
{
    key_t proj_key = -1;
    int g_semid = -1;
    
    proj_key = ftok(WD_PATH, proj_id);
    if (-1 == proj_key)
    {                   
        return -1;
    }
    

    g_semid = semget(proj_key, N_SEM, SEM_FLAG | IPC_CREAT);
    if (-1 == g_semid)
    {                
        return -1;
    }
        
    return g_semid;
}

static int InitWDProc()
{

    g_wd_pid = fork();
    if (-1 == g_wd_pid)
    {
        return WD_E_EXEC;
    }
    else if (!g_wd_pid) /* this is wathdog proc */
    {   
        execvp(g_argv[0], g_argv);    
        
        perror(exec_error_message);
        exit(0);
    }
    else 
    {
        if (-1 == semop(g_semid, g_op + WD_READY_SEM, 1LU))
        {
            return WD_E_SEM;
        }
    }

    return WD_OK;
}

static int InitGlobals(int argc, char *argv[], int wd_id)
{
    int status = WD_OK;

    g_semid = CreateSemaphore(wd_id);
    if (-1 == g_semid)
    {
        return WD_E_SEM;
    }

    status = InitGArggv(argc, argv, g_semid);
    if (status)
    {
        semctl(g_semid, 0, IPC_RMID);

        return WD_E_MEM;
    }    
    
    status = InitSigAction();
    if (status)
    {
        puts(strerror(status));
        DestroyGArgv();
        semctl(g_semid, 0, IPC_RMID);

        return WD_E_SIGACT;
    }


    return status;
}

int WDStart(int argc, char *argv[], int wd_id)
{
    int status = 0;
    int semval = -1;
    
    scd_t *scheduler = NULL;
          
    status = InitGlobals(argc, argv, wd_id);
    if (status)
    {
        return status;
    }

    semval = semctl(g_semid, WD_READY_SEM, GETVAL);
    if (0 == semval) /* Initial run: APP should start WD */
    {
        status = InitWDProc();
        if (status)
        {
            DestroyGArgv();
            semctl(g_semid, 0, IPC_RMID);

            return status;
        }
    }
    else if (-1 == semval)
    {
        DestroyGArgv();
        semctl(g_semid, 0, IPC_RMID);

        return WD_E_SEM;
    }
    else /* APP revived by WD */
    {
        g_wd_pid = getppid();  
        if (-1 == semop(g_semid, g_op + APP_READY_SEM, 1LU))
        {
            return WD_E_SEM;
        }
    }
        
    scheduler = Schedule(scheduler);
    if (!scheduler)
    {
        DestroyGArgv();
        semctl(g_semid, 0, IPC_RMID);

        return WD_E_MEM;
    }
    
    return InitAppWatch(scheduler);
}

#define N_SIG2_TRIES (2)
#define SEC_TO_SLEEP (2) /* "enough" to have been sent a sig back */
void WDStop()
{
    int count_sig = 0;

    g_should_tasks_stop = 1;
    
    for (; !g_confirmed_wd_to_die && N_SIG2_TRIES > count_sig; ++count_sig)
    {
        int time_to_sleep = SEC_TO_SLEEP; 
        
        kill(g_wd_pid, SIGUSR2);
        while (!g_confirmed_wd_to_die && 0 < time_to_sleep)
        {
            time_to_sleep = sleep(time_to_sleep);
        }
    } 
    
    /* Plan B: "Dirty" watchdog Kill */
    if (!g_confirmed_wd_to_die)
    {
        puts(RED"APP: Dirty WD termination"RESET);
        kill(g_wd_pid, SIGKILL);
    }
    
    semctl(g_semid, 0, IPC_RMID);
    
    DestroyGArgv();
    
    waitpid(g_wd_pid, NULL, 0);
    pthread_join(g_watch_thread_id, NULL);    
}
#undef N_SIG2_TRIES
#undef SEC_TO_SLEEP