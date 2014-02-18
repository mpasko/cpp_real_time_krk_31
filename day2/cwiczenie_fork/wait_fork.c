
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    int status;
    pid = fork();
    if ( pid == 0 )
    {
        printf("CHILD, sleep\n");
        sleep(4);
        exit(10);
    }
    else
    {
        printf("PARENT, wait\n");
        pid = wait(&status);

        if (pid == -1)
        {
            printf("PARENT %s\n", strerror(errno));
            exit(1);
        }
        printf("PARENT, child status = %d [%d]\n", pid, WEXITSTATUS(pid));
    }
}
