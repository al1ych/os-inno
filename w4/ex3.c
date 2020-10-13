#include "stdio.h"

int main(void)
{
  char* s[100];
  while (1)
  {
    scanf("%100s", &s);
    printf("executing %s\n", s);
    system(s);
  }

  return 0;
}

