#include "stdio.h"
#include "sys/types.h"
#include "unistd.h"

int main(void)
{
  const int n = 10;

  pid_t pid = fork();

  char* who = (pid == 0 ? "child" : "parent"); // if the pid of this procces is 0, it means it's been launched from a parent process so we are the child process in this situation
  printf("Hello from %s [%d - %d]\n", who, pid, n);
  
  /*
   the output will look something like this:
    Hello from parent [83346 - 10] // first, we're in the parent process with this pid
    Hello from child [0 - 10] // then, the child process will be launched by the first one
    Hello from parent [83348 - 10] // then the shell script will launch the .c code again
    Hello from child [0 - 10] // the child process of the secondly launched code of the .c code
    Hello from parent [83350 - 10] // ...and so on...
    Hello from child [0 - 10]
    Hello from parent [83352 - 10]
    Hello from child [0 - 10]
    Hello from parent [83354 - 10]
    Hello from child [0 - 10]
    Hello from parent [83356 - 10]
    Hello from child [0 - 10]
    Hello from parent [83358 - 10]
    Hello from child [0 - 10]
    Hello from parent [83360 - 10]
    Hello from child [0 - 10]
    Hello from parent [83362 - 10]
    Hello from child [0 - 10]
    Hello from parent [83364 - 10]
    Hello from child [0 - 10]
   */

  return 0;
}

