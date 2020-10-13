#include <stdio.h>
#include <stdlib.h>

int main()
{
  char **s = malloc(sizeof(char *));
  char foo[] = "Hello World";
  *s = foo;
  printf("s is %s\n", *s); // compiles even with printf("...", s);  without seg faults
  s[0] = foo;
  printf("s[0] is %s\n", s[0]);
  return 0;
}
