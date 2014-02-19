#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <iomanip>

#include <sys/wait.h>


int main(int argc, char *argv[])
{
    pid_t ppid;

    setbuf(stdout, NULL);       /* Disable buffering of stdout */

    switch (fork())
    {
    case -1:
        exit(-1);

    case 0:             /* Child */
        while ((ppid = getppid()) != 1)     /* Loop until orphaned */
        {
            printf("Child running (parent PID=%ld)\n", (long) ppid);
            sleep(1);
        }
        printf("Child is orphaned (parent PID=%ld)\n", (long) ppid);
        exit(EXIT_SUCCESS);

    default:            /* Parent */
        printf("Parent (PID=%ld) sleeping\n", (long) getpid());
        sleep(3);                           /* Give child a chance to start */
        printf("Parent exiting\n");
        exit(EXIT_SUCCESS);
    }
}
