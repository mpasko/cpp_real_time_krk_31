#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main()
{

    cout << "A" << endl;   cout.flush();

    pid_t pid = fork();
     cout << "B" << endl; cout.flush();
    fork(); cout << "C" << endl; cout.flush();
    fork(); cout << "D" << endl; cout.flush();
}
