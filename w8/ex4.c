#include "stdio.h"
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include <sys/resource.h> 
#include <sys/time.h> 

int main(void)
{
  const unsigned long long mem = 15; // 15mb
  int who = RUSAGE_SELF;
  struct rusage u;
  int ret;
  for (int t = 0; t < 10; t++)
  {
    void* x = malloc(mem * 1024ll*1024);
    memset(x, 0, mem * 1024ll*1024);
    ret = getrusage(who, &u);
    if (!ret)
      printf("%ld\n", u.ru_maxrss);
    sleep(1);
  }
}
