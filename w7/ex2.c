#include "stdio.h"
#include <stdlib.h>

int N;

int main(void)
{
  printf("hello, enter N:");
  scanf("%i", &N);

  int* a = (int*) calloc(N, sizeof(int));
  
  for (int i = 0; i < N; i++)
  {
    a[i] = i;
  }

  for (int i = 0; i < N; i++)
  {
    printf("%d ", a[i]);
  }

  free(a);

  return 0;
}

