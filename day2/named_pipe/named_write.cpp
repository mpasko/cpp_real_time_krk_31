#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

char fifo[] = "named-fifo";

int main()
{
    char message[] = "message\n";
    int fd;

    fd = open( fifo, O_WRONLY | O_NONBLOCK );

    int n = write(fd, message, 9);

    cout << "Num written = " << n << endl;

    return 0;
}

