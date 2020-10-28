#include <stdio.h>
int main(void) {
  printf("Hello");
  fork();
  printf("\n");
  return 0;
}
