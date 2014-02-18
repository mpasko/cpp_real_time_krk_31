#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSGSIZE 16

char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";
char *msg3 = "hello, world #3";

main(int argc, char * argv[])
{
    char inbuf[MSGSIZE];
    int p[4], j;
    if (argc == 1){
        printf("usage:\n%s {filename}\n",argv[0]);
        exit(0);
    }
    // otwieramy potok
    if(pipe(p) == -1)
    {
        perror("utworzenie potoku");
        exit(1);
    }
    if (0 == fork()) {
        dup2(p[1],fileno(stdout));
        close(p[0]);
        close(p[1]);
    // piszemy do potoku
        /*
    write(1, msg1, MSGSIZE);
    write(1, msg2, MSGSIZE);
    write(1, msg3, MSGSIZE);
    */
        execlp("ps","ps","-e",NULL);
    }
    else
    {
            int fd;
    // odczytujemy z potoku
            dup2(p[0],fileno(stdin));
            close(p[0]);
            close(p[1]);
            fd = open(argv[1],"w");
            dup2(fd,fileno(stdout));
            close(fd);
            execlp("sort","sort","-g",NULL);
  /*
        for(j = 0; j < 3; j++)
        {
            read(0, inbuf, MSGSIZE);
            printf("%s\n", inbuf);
        }
        */
    }
    exit(0);
}
