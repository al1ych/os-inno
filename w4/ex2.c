#include "stdio.h"
#include "sys/types.h"
#include "unistd.h"

int main(void)
{
  const int N = 3;

  for (int t = 0; t < N; t++)
  {
    pid_t pid = fork();
  }
  sleep(7); // for us to be able to call pstree

  /*

     for N = 3:
    -+= 86771 timurnugaev ./ex2  // the original parent process
     |-+- 86772 timurnugaev ./ex2
     | |-+- 86775 timurnugaev ./ex2
     | | \--- 86778 timurnugaev ./ex2
     | \--- 86777 timurnugaev ./ex2
     |-+- 86773 timurnugaev ./ex2
     | \--- 86776 timurnugaev ./ex2
     \--- 86774 timurnugaev ./ex2

     created 8 processes: 2^3 = 8
     parent process calls 3 child processes which also fork three times
     


     for N = 5:
      -+= 87161 timurnugaev ./ex2
       |-+- 87162 timurnugaev ./ex2
       | |-+- 87164 timurnugaev ./ex2
       | | |-+- 87168 timurnugaev ./ex2
       | | | |-+- 87176 timurnugaev ./ex2
       | | | | \--- 87192 timurnugaev ./ex2
       | | | \--- 87189 timurnugaev ./ex2
       | | |-+- 87175 timurnugaev ./ex2
       | | | \--- 87191 timurnugaev ./ex2
       | | \--- 87187 timurnugaev ./ex2
       | |-+- 87167 timurnugaev ./ex2
       | | |-+- 87174 timurnugaev ./ex2
       | | | \--- 87190 timurnugaev ./ex2
       | | \--- 87186 timurnugaev ./ex2
       | |-+- 87173 timurnugaev ./ex2
       | | \--- 87188 timurnugaev ./ex2
       | \--- 87184 timurnugaev ./ex2
       |-+- 87163 timurnugaev ./ex2
       | |-+- 87166 timurnugaev ./ex2
       | | |-+- 87172 timurnugaev ./ex2
       | | | \--- 87185 timurnugaev ./ex2
       | | \--- 87183 timurnugaev ./ex2
       | |-+- 87171 timurnugaev ./ex2
       | | \--- 87182 timurnugaev ./ex2
       | \--- 87181 timurnugaev ./ex2
       |-+- 87165 timurnugaev ./ex2
       | |-+- 87170 timurnugaev ./ex2
       | | \--- 87180 timurnugaev ./ex2
       | \--- 87178 timurnugaev ./ex2
       |-+- 87169 timurnugaev ./ex2
       | \--- 87179 timurnugaev ./ex2
       \--- 87177 timurnugaev ./ex2

       created 32 processes: 2^5 = 32


     */


  return 0;
}

