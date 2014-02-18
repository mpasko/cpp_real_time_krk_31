#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pid_info.h"
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include "wait_info.h"

int main(int argc, char *argv[])
{
    pid_t pid;
    pid_t w;

    int status;

    pid = fork(); 
    if ( pid == 0 )  /* CHILD*/
    {
        printf("CHILD, sleep, %d %s\n", getpid(), argv[1] );

        pause();

        exit( atoi(argv[1] ) );
    }
    else    /*  PARENT */
    {
        printf("PARENT, wait\n");
        
        while ( ( w = waitpid( pid, &status, WNOHANG) ) == 0 )
        {
            printf("Parent wait...\n");
            sleep(1);
        }

        wait_info(w, status);
    }
}
