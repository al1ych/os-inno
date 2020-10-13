#include "stdio.h"

int main(void)
{
  while (1)
  {
    char buffer[32];
    char *s = buffer;
    size_t bufsize = 32;

    getline(&s, &bufsize, stdin);
    printf("executing %s\n",buffer);

    system(s);
  }

  return 0;
}

