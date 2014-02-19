#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>


void printRusage(const struct rusage *ru)
{

    printf("CPU time (secs):         user=%.3f; system=%.3f\n",
           ru->ru_utime.tv_sec + ru->ru_utime.tv_usec / 1000000.0,
           ru->ru_stime.tv_sec + ru->ru_stime.tv_usec / 1000000.0);
    printf("Max resident set size:   %ld\n", ru->ru_maxrss);
    printf("Integral shared memory:  %ld\n", ru->ru_ixrss);
    printf("Integral unshared data:  %ld\n", ru->ru_idrss);
    printf("Integral unshared stack: %ld\n", ru->ru_isrss);
    printf("Page reclaims:           %ld\n", ru->ru_minflt);
    printf("Page faults:             %ld\n", ru->ru_majflt);
    printf("Swaps:                   %ld\n", ru->ru_nswap);
    printf("Block I/Os:              input=%ld; output=%ld\n",
           ru->ru_inblock, ru->ru_oublock);
    printf("Signals received:        %ld\n", ru->ru_nsignals);
    printf("IPC messages:            sent=%ld; received=%ld\n",
           ru->ru_msgsnd, ru->ru_msgrcv);
    printf("Context switches:        voluntary=%ld; "
           "involuntary=%ld\n", ru->ru_nvcsw, ru->ru_nivcsw);
}
int main()
{
    int i;
    struct rusage ru;

    pid_t pid = fork();
    pid_t r;
    int status;

    if ( pid > 0 )
    {

        sleep(2);

        kill(pid, SIGSTOP);
        r = wait4(pid, &status, WUNTRACED, &ru);

        printRusage( &ru );
  
        if (r == pid)
            kill(pid, SIGCONT);

        
        wait(&status);
    }
    else
    {

        for( i=0; i<10; i++)
        {
            sleep(1);
            printf("CHILD is looping\n");
        }


    }

}

