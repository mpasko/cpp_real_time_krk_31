
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "wait_info.h"

int main(int argc, char * const argv[])
{
    pid_t pid;
    pid = fork();
    if (0==pid)
    {
        if (argc > 1)
        {
            execvp(argv[1], ++argv);
        }
    }
}
