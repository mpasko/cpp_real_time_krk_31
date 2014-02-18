#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char **argv)
{

    if( argc == 1 )
        printf("Brak parametrow wywolania\n");
    else
    {
        printf("Argumenty:\t");

        while( --argc > 0)
            printf("%s\t", *++argv);

        printf("\n");
    }

    // putenv() i getenv()
    char myEnvVar[] = "QQ=to tylko test";
    putenv(myEnvVar);

    setenv("XX", "testowy ciag drugi", 1);

    printf("1 Pobralem QQ   = %s\n", getenv("QQ"));
    printf("2 Pobralem XX   = %s\n", getenv("XX"));
    printf("3 Pobralem USER = %s\n", getenv("USER"));
    printf("\n");

    while(*environ)
        printf("%s\n", *environ++);

    printf("\n");

    printf("3 Pobralem USER = %s\n", getenv("USER"));

    return 0;
}
