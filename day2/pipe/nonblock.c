// nieblokujace zapisy i odczyty
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#define MSGSIZE 6

char *msg1 = "hello";
char *msg2 = "bye!!";

int fatal(char *s)
{
    perror(s);
    exit(1);
}

int parent(int p[2])
{
    int nread;
    char buf[MSGSIZE];

    close(p[1]);
    for(;;)
    {
        switch(nread = read(p[0], buf, MSGSIZE))
        {
        case -1:
            // czy jest cos w potoku
            if(errno == EAGAIN)
            {
                printf("potok pusty\n");
                sleep(1);
                break;
            }
            else
                fatal("wowlanie read");
        case 0:
            // potok zamkniety
            printf("Koniec\n");
            exit(0);
        default:
            printf("MSG = %s\n",buf);
        }
    }
}

int child(int p[2])
{
    int count;

    close(p[0]);
    for(count = 0; count < 3; count++)
    {
        write(p[1], msg1, MSGSIZE);
        sleep(3);
    }

    // komunikat koncowy
    write(p[1], msg2, MSGSIZE);
    exit(0);
}

main()
{
    int pfd[2];

    // otworz potok
    if(pipe(pfd) == -1)
        fatal("wywolanie pipe");

    // ustaw znacznik O_NONBLOCK dla p[0]
    if( fcntl(pfd[0], F_SETFL, O_NONBLOCK) == -1)
        fatal("wywolanie fcntl");

    switch(fork())
    {
    case -1: // blad
        fatal("wywolanie fork");
    case 0:  // potomek
        child(pfd);
    default: // rodzic
        parent(pfd);
    }
}
