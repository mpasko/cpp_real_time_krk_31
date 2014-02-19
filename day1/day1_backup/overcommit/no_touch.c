#include <stdio.h>
#include <stdlib.h>

const size_t hundredmb = 1024*1024*100;

int main (void)
{
    size_t n = 0;

    while (1)
    {
        if (malloc(hundredmb) == NULL)
        {
            printf("malloc failure after %zd MiB\n", n);
            return 0;
        }
        n += 100;
        printf ("got %zd MiB\n", n);
    }
}