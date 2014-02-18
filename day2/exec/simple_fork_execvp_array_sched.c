#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>

int spawn (char* program, char** arg_list)
{
    pid_t child_pid;

    child_pid = fork ();

    if (child_pid != 0)
        return child_pid;
    else
    {
        struct sched_param param;
        param.sched_priority = 10;

        sched_setscheduler( getpid(), SCHED_RR, &param);

        execvp (program, arg_list);

        //error
        fprintf(stderr, "an error occurred in execvp\n");
        abort ();
    }
}

int main ( int argc, char *argv[]  )
{
    pid_t child_pid_spawn;
    pid_t child_pid_wait;
    int status;

    child_pid_spawn = spawn (argv[1], &argv[1]);
    printf ("wait..\n");

    child_pid_wait = wait(&status);
    printf("post wait child_pid_spawn: %d, child_pid_wait: %d\n", child_pid_spawn, child_pid_wait);

    return 0;
}
