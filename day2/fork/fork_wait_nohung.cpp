#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <sys/wait.h>
#include <errno.h>

using namespace std;

int main( ) 
{
  pid_t  pid, w;
  int    status;

  static char buffer[10];

  pid = fork();
  if (pid == 0) 
  {                            
     strcpy(buffer, "CHILD...\n");
     sleep(2);
  } 
  else 
  {                             
    strcpy(buffer, "PARENT..\n");
  }

  for (int i=0; i < 3; ++i) 
  {          
    sleep(1);
    write(fileno(stdout), buffer, sizeof(buffer));
  }
  
  if (pid > 0 )
  {
    //oczekiwanie blokujace
    // cout << "blokujace oczekiwanie" << endl;
    // cout.flush();

    // w = wait(&status);
    // if ( w == -1 )
    // {
    //     cout << strerror( errno ) << endl;
    // }
    // else
    //   cout << "Po oczekiwaniu na PID: " << dec << w << "  status == "
    //        << setw(4) << setfill('0') << hex
    //        << setiosflags(ios::uppercase) << status << endl;

  
    //oczekiwanie nie blokujace
    while(waitpid(pid, &status, WNOHANG) == 0) 
    {
      printf("Ciagle czekam ......\n");
      sleep(1);
    }


    if(WIFEXITED(status)) 
    {
      uint exit_status = WEXITSTATUS(status);
      printf("Kod wyjscia procesu %d == %d\n", pid, exit_status);
    }
  }

  return 0;
}
