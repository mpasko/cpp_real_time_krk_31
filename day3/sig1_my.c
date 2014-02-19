#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void catch_int(int signum)
{
    printf("Handler int %d\n", signum);
}

void catch_usr(int signum)
{
    printf("Handler usr %d\n", signum);
}

int main(int argc, char const *argv[])
{
    int i;
    static struct sigaction action;
    static struct sigaction old_action;
    sigset_t set1, set2;

    action.sa_handler = catch_int;
    sigaction(SIGINT, &action, &old_action);

    printf("PID: %d\n",getpid());

    signal(SIGUSR1, &catch_usr);
    //signal(SIGINT, SIG_IGN);

    sigfillset(&set1);
    sigfillset(&set2);
    sigdelset(&set2,SIGINT);
    sigdelset(&set2,SIGUSR1);

    sigprocmask(SIG_SETMASK, &set1, &set2); //sigint zablokowane

    printf("CRIT SECT\n");

    raise(SIGINT);

    printf("CRIT END\n");

    sigprocmask(SIG_SETMASK, &set2, NULL); //sigint odblokowane

    raise(SIGUSR1);

    printf("END\n");

    for( i=0; i<30; i++)
    {
        printf(".");
        sleep(1);
    }

    printf("Ignore\n");
    
    for( i=0; i<30; i++)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
    }    
    printf("\n");
    return 0;
}
