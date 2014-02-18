#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <iomanip>

#include <sys/wait.h>
using namespace std;


using namespace std;

int
main( ) 
{
  pid_t  pid, w;
  int    status;

  static char buffer[10];

  pid = fork();
  if (pid == 0) 
  {    
     sleep(2);                         // In the child process
     strcpy(buffer, "CHILD...");
     
  } 
  else 
  {                             // In the parent process
    strcpy(buffer, "PARENT..");
  }

  for (int i=0; i < 3; ++i) {          // Both processes do this
    sleep(1);                          // 3 times each.
    write(1, buffer, sizeof(buffer));
  }
  
  if (pid > 0 )
  {

    while(waitpid(pid, &status, WNOHANG) == 0) {
      printf("Ciagle czekam ......\n");
      sleep(1);
    }

    // test zako.czenia potomka
    if(WIFEXITED(status)) {
      uint exit_status = WEXITSTATUS(status);
      printf("Kod wyjscia procesu %d to %d\n", pid, exit_status);
    }
  }


  return 0;
}
