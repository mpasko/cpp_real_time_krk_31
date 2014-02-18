#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const size_t hundredmb = 1024*1024*100;

int main (void)
{
    ssize_t n = 0;
    char *p;

    while (1)
    {
        if ((p = malloc(hundredmb)) == NULL)
        {
            printf("malloc failure after %zd MiB\n", n);
            return 0;
        }
        
        memset (p, 0, (hundredmb));
        n += 100;

        printf ("got %zd MiB\n", n);
    }
}
