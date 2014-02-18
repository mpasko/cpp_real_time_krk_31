#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "wait_info.h"

#define BUF_SZ 200

int main(int argc, char * const argv[])
{
    pid_t pid;
    int last=0;
    char buf[BUF_SZ];
    char * pch;
    char * arguments[50];
    char command[50];
    int status;
    int i;
    int j;
    printf("\n>");
    while (fgets(buf,BUF_SZ,stdin))
    {
        //printf("DEBUG got it: %s\n",buf);
        if (buf==NULL)
        {
            exit(last);
        }
        else
        {
            pch = strtok (buf, " ");
            //printf("DEBUG toked: %s\n",pch);
            strncpy(command, pch, 50);
            arguments[0] = (char *)malloc(50);
            strncpy(arguments[0], pch, 50);
            //arguments[0] = malloc(strlen(pch));
            i=1;
            while(pch!=NULL){
                pch = strtok (NULL, " ");
                //printf("DEBUG toked: %s\n",pch);
                arguments[i] = (char *)malloc(50);
                if (pch != NULL)
                {
                    strncpy(arguments[i], pch, 50);
                }
                else
                {
                    arguments[i]=pch;
                }
                //printf("DEBUG next arg %s\n",arguments[i]);
                ++i;
            }
        }
        //printf("DEBUG before fork\n");
        //for (j = 0; j < i; ++j)
        //{
        //    printf("DEBUG %s\n",arguments[j]);
        //}
        pid = fork();

        if (0==pid)
        {
            execvp(command, arguments);
            return 1;
        }
        else
        {
            //printf("DEBUG parent");
            last=wait(&status);
            last=WEXITSTATUS(last);
            printf("\n>");
        }
    }
}
