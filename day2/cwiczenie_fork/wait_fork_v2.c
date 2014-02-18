
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "wait_info.h"

int main(int args, char * argv[])
{
    pid_t pid;
    pid_t w;
    int status;
    pid = fork();
    int arg = 10;

    if ( pid == 0 )
    {
        printf("CHILD, sleep, %d\n", getpid());
        if (args>1){
            arg=atoi(argv[1]);
            pause();
        }

        //sleep(4);
        wexit(arg);
    }
    else
    {
        printf("PARENT, wait\n");

        /* *x/
        pid = wait(&status);

        if (pid == -1)
        {
            printf("PARENT %s\n", strerror(errno));
            exit(1);
        }
        /* */

        printf("PARENT wait...\n");

        while (w = waitpid(pid, &status, WNOHANG)==0)
        {

            sleep(1);
        }
        //printf("PARENT, child status = %d [%d]\n", pid, WEXITSTATUS(pid));
        wait_info(w,status);
    }
}
