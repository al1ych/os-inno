#include "stdio.h"
#include "limits.h"
#include "stdlib.h"

#define MAXN 1048576
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
  
struct P
{
  int a, b; // arrival time, burst time
  int ct, tat, wt; // completion time, turnaround time, waiting time
  int bt_left; // burst time left currently
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
  int n, q; // num of procs, quantum
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
    a[i].bt_left = a[i].b; // in the beginning burst time left = burst time
  }
  printf("Enter the quantum for Round Robin algo: quantum = ");
  scanf("%i", &q);

  // processing
  qsort(a, n, sizeof(struct P), comp); // sorting by arrival time (sequential execution)

  int bt_total = 0; // total burst time (all the processess combined executing time)
  int setback = a[0].a;
  for (int i = 0; i < n; i++)
  {
    bt_total += a[i].bt_left;
    a[i].a -= setback; // shifting it all so that AT of the first process is 0
  }

  int time = 0;
  while (bt_total > 0)
  {
    for (int i = 0; i < n; i++)
    {
      if (a[i].a <= time && a[i].bt_left != 0)
      {
        int delta = a[i].bt_left;
        a[i].bt_left = max(0, a[i].bt_left - q); // 0 if a[i].bt_left < q is left in bt, otherwise quantum less
        delta -= a[i].bt_left; // delta = (a[i].bt_left before trying to subtract quantum) - (a[i].bt_left after subtracting quantum)
        // note that delta can be less than quantum
        
        bt_total -= delta; 
        time += delta;

        if (a[i].bt_left == 0) // if it was the last cycle of the process
        {
          // printf("delta %i\n", delta);
          // a[i].a += setback; // shift it back
          a[i].ct = time; // + setback
          a[i].wt = a[i].ct - a[i].a - a[i].b;
          a[i].tat = a[i].b + a[i].wt;
        }
        
        wt_av += a[i].wt;
        tat_av += a[i].tat;
      }
    }
    // printf("bt total: %i\n", bt_total);
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
    3 2 4 3 6 1 4 2
     */

  /*
comparing output of this algo we can conclude that performance depends on quantum which you have to specify manually
in case of the first one (fcfs) and the second algo (Short first), it's not the case
    
first (FCFS):
P#	AT	BT	CT	TAT	WT
P1	1	  4 	5	  4 	0
P2	2	  4	  9	  7	  3
P3	3	  6	  15  12  6
Average TAT: 7.666667
Average WT: 3.000000

average WT is less on FCFS than on Round Robin [*](same reason as the one I described below, in the second algo comparison) 

p. s. and in this case it's actually equal to avg wt of short first, but in general, it's greater than or equal to the avg wt on short first
p. p. s. same logic applies to TAT


second (short first):
P#	AT	BT	CT	TAT	WT
P1	1	  4	  5	  4	  0
P2	2	  4	  9	  7	  3
P3	3 	6 	15	12	6
Average TAT: 7.666667
Average WT: 3.000000

average WT is less on Short First on average than on Round Robin [*](because Round Robin opens a process and then after the process is done with the portion (quantum) of work it's allowed to execute, it has to wait until it's its turn again, and so we have a lot of processess waiting (all of the ready ones are waiting, actually), so the average waiting time increases this way)
but on Round Robin you can choose the optimal value of the quantum that you need exactly for your system, having just a little bit more control over the scheduler algorithm
and Round Robin allows this kind of concurrent solution so if there's two processess with the same AT and BT, their WTs will be equal
so I would say it's better suitable for systems where concurrence needs to take place

p. s. same logic applies to TAT


third (quantum=2):
P#	AT	BT	CT	TAT	WT
P1	0	  4	  8	  8	  4
P2	1	  4 	10	9 	5
P3	2	  6 	14	12  6
Average TAT: 9.666667
Average WT: 5.000000
   */
  return 0;
}

