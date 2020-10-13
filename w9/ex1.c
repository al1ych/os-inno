#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const int N = 1000;

int str_to_int(char *s)
{
  int p = 1, res = 0;
  for (int i = strlen(s) - 1; i >= 0; i--)
  {
    int d = s[i] - '0';
    res += d * p;
    p *= 10;
  }
  return res;
}

typedef struct {
    unsigned char t;
    int ref;
    int free;
} pframe;

int main(int argc, char **argv)
{
  freopen("page-refs.in", "r", stdin);
  int pframes = str_to_int(argv[1]), misses = 0, ref = 0;
  pframe *pages = malloc(sizeof(pframe) * pframes);

  for (int i = 0; i < pframes; i++)
  {
      pages[i].t = 0;
      pages[i].ref = -1;
      pages[i].free = 1;
  }

  for (int t = 0; t < N; t++)
  {
    scanf("%d", &ref);
    int m = 1, pg_age;

    for (int i = 0; i < pframes; i++)
    {
      if (pages[i].ref == ref)
      {
        pg_age = i;
        m = 0;
        goto found;
      }
    }

    for (int i = 0; i < pframes; i++)
    {
      if (pages[i].free == 1)
      {
        pg_age = i;
        pages[i].free = 0;
        goto found;
      }
    }

    pg_age = -1;
    int min = INT_MAX;
    for (int i = 0; i < pframes; i++)
    {
      if (pages[i].t < min)
      {
        pg_age = i;
        min = pages[i].t;
      }
    }

    // found marker for goto here
    found:
    // found marker

    pages[pg_age].t = pages[pg_age].t >> 1 | (1 << 7);
    pages[pg_age].ref = ref;

    for (int i = 0; i < pframes; i++)
      if (i != pg_age)
        pages[i].t = pages[i].t >> 1;

    misses += m;
  }

  printf("\nfor %d page frames\n", pframes);
  printf("hits: %d\n", N - misses);
  printf("misses: %d\n", misses);
  printf("hit/miss: %lf\n\n", (N-misses)*1./misses);

  return 0;
}
