#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "pid_info.h"

using namespace std;

int main()
{

    cout << "A" << endl;   cout.flush();

    pid_t pid;

    pid = fork(); 
    if ( pid == 0 )
    {
        cout << "B" << endl; cout.flush();
        sleep(1);
        pid_info("child B");

        pid = fork(); 

        if ( pid == 0 )
        {
            cout << "C" << endl; cout.flush();
            sleep(1);
            pid_info("child C");
            pid = fork(); 
            if ( pid == 0 )
            {
                cout << "D" << endl; cout.flush();
                sleep(1);
                pid_info("child D");

            }
        }

    }
   
}
