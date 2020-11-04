#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"

const int N = 20;

int main()
{
  freopen("ex1.txt", "w", stdout);
  int dev_random_file = open("/dev/random", O_RDONLY);
  if (dev_random_file < 0)
  {
    printf("oops something went wrong; errcode: 1");
    return 0;
  }

  char s[N];
  int sz = 0;
  while (sz < N)
  {
    int rc_sz = read(dev_random_file, s + sz, N - sz);
    if (rc_sz < 0)
    {
      printf("oops something went wrong; errcode: 2");
      return 0;
    }
    sz += rc_sz;
  }

  close(dev_random_file);
  printf("%s\n", s);
  return 0;
}
