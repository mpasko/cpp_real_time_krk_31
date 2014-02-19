#include <stdio.h>
#include <stdlib.h>

#define MSG_SIZE 5

char msg1[] = "abcd";
char msg2[] = "efgh";
char msg3[] = "ijkl";

//abc d_e fgh _ij kl_
//123 123 123 123 123

int main(int argc, char const *argv[])
{
    int p[2];
    int i;
    char rcv_buf[3];
    int num_rcv_bytes;

    pipe(p);


    //   $ ls -al | sort

    // 0 - STDIN
    // 1 - STDOUT
    // 2 - STDERR




    if ( fork () == 0 )
    {
        close( p[0] );
        write(p[1], msg1, MSG_SIZE);
        write(p[1], msg2, MSG_SIZE);
        write(p[1], msg3, MSG_SIZE);
        write(p[1], msg1, MSG_SIZE);
    }
    else
    {
        close( p[1] );

        for(i=0; i<5; i++)
        {
            num_rcv_bytes = read(p[0], rcv_buf, 5);
            printf("%d\n%s\n", num_rcv_bytes, rcv_buf);
        }
    }

    return 0;
}