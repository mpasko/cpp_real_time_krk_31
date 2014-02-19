#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h> /* vsnprintf() */

int counter = 0;

void myprintf(FILE *fp, char *fmt, ...)
{
    char buff[512];
    int rc,fd;
    va_list argh;
    va_start (argh, fmt);

    rc = vsnprintf(buff, sizeof buff, fmt, argh);
    if (rc < 0  || rc >= sizeof buff)
    {
        rc = sprintf(buff, "Argh!: %d:\n", rc);
    }

    if (!fp) fp = stderr;
    fd = fileno(fp);
    if (fd < 0) return;
    if (rc > 0)  write(fd, buff, rc);
    return;
}

void handler(int signal)
{
    counter++;
    printf("Signal handler called = %d\n", counter);
    fflush(stdout);
}

int main(int argc, char const *argv[])
{
    int i;
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;
    sigaction( SIGRTMIN, &sa, NULL);

    for(i = 0; i<5; i++)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
    }

    printf("Signal handler called = %d", counter);

    return 0;
}