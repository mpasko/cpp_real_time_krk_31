#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "pid_info.h"
#include "wait_info.h"

int main()
{
    pid_t pid;
    pid_t ppid;
    int status;
    pid_t chld_pid;
    pid_t chld_pid_new;


    chld_pid_new = fork();
    if (  chld_pid_new == 0 )
    {
        pid_info("CHILD");

        char* const av[] = {"als", "-al", (char*)0};

        execvp(av[0], av );
    }
    else
    {
        pid_info("PARENT");

        printf("pre wait\n");

        chld_pid = wait(&status);
        wait_info(chld_pid, status);
    }
}