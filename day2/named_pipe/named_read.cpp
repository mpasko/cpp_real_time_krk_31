#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define BUF_SIZE 64

char fifo_name[] = "named-fifo";

int main(int argc, char **argv)
{

    int fd;

    char buf[BUF_SIZE];

    if (  mkfifo( fifo_name, 0666 ) == -1  )
    {
        //error
        std::cout << strerror( errno ) << std::endl;

    }

    fd = open(fifo_name, O_RDWR);

    while( 1 )
    {
        memset(buf, 0, sizeof(buf));
        int num_bytes = read(fd, buf, BUF_SIZE-1);
        std::cout << num_bytes << " " << buf << std::endl;
    }
}
