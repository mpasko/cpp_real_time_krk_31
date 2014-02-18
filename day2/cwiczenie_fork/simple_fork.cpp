#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main()
{
    cout << "A" << endl;
    cout.flush();
    
    for(int i =0; i<4; ++i)
    {
        int mine = fork();
        int parent = getppid();
        cout << char((int)'B'+i) << "(pid:"<< mine <<" parent:"<<parent<<")"<< endl;
    }
}
