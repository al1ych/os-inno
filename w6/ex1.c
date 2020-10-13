#include "stdio.h"
#include "limits.h"
#include "stdlib.h"

#define MAXN 1048576
  
struct P
{
  int a, b; // arrival time, burst time
  int ct, tat, wt; // completion time, turnaround time, waiting time
};

int comp(const void *p1, const void *p2)
{
  struct P l = *(struct P*) p1;
  struct P r = *(struct P*) p2;
  return l.a - r.a;
}

int main(void)
{
  // init
  int n;
  struct P* a = malloc(MAXN * sizeof(struct P)); // arrival times + burst times
  float wt_av = 0, tat_av = 0; // average waiting time and turn around time

  // input
  printf("How many proccesses? N = ");
  scanf("%i", &n);
  for (int i = 0; i < n; i++)
  {
    printf("Arrival time for process #%i = ", i + 1);
    scanf("%i", &((a + i)->a));
    printf("Burst time for process %i = ", i + 1);
    scanf("%i", &((a + i)->b));
  }

  // processing
  qsort(a, n, sizeof(struct P), comp); // sorting by arrival time (sequential execution)

  a[0].tat = a[0].b; // first one doesn't wait in this implementation
  a[0].wt = 0; // first one doesn't wait at all
  a[0].ct = a[0].a + a[0].tat;

  wt_av += a[0].wt;
  tat_av += a[0].tat; // BASE CASE

  for (int i = 1; i < n; i++) // GENERAL CASE
  {
    a[i].wt = (a[i - 1].ct + a[i].b) - (a[i].a + a[i].b); // real minus expected = waiting time
    a[i].tat = a[i].b + a[i].wt; // waiting + executing (burst)
    a[i].ct = a[i].tat + a[i].a; // this proccess completes when the prev completes + this waits + this bursts

    wt_av += a[i].wt;
    tat_av += a[i].tat;
  }
  
  tat_av /= n * 1.; // average tat
  wt_av /= n * 1.; // average wt

  // output
  printf("\nP#\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++)
  {
    printf("P%i\t%i\t%i\t%i\t%i\t%i\n", i + 1, a[i].a, a[i].b, a[i].ct, a[i].tat, a[i].wt);
  }
  printf("Average TAT: %f\n", tat_av);
  printf("Average WT: %f\n", wt_av);

  /* test
    3 2 4 3 6 1 4
     */
  return 0;
}

