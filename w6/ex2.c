#include "stdio.h"
#include "limits.h"
#include "stdlib.h"

#define MAXN 1048576
  

struct queue { 
  int top_e, bot_e, cur_sz; 
  int* a; 
}; 

struct queue* setup_queue() 
{ 
  struct queue* queue = (struct queue*) malloc(sizeof(struct queue)); 
  queue->top_e = queue->cur_sz = 0; 
  queue->bot_e = MAXN - 1; 
  queue->a = (int*) malloc(MAXN * sizeof(int)); 
  return queue; 
} 

int empty(struct queue* queue) 
{ 
  return (queue->cur_sz == 0); 
} 

void push(struct queue* queue, int item) 
{ 
  queue->bot_e = (queue->bot_e + 1) % MAXN; 
  queue->a[queue->bot_e] = item; 
  queue->cur_sz = queue->cur_sz + 1; 
} 

int pop(struct queue* queue) 
{ 
  if (empty(queue)) 
    return INT_MIN; 
  int item = queue->a[queue->top_e]; 
  queue->top_e = (queue->top_e + 1) % MAXN; 
  queue->cur_sz = queue->cur_sz - 1; 
  return item; 
} 

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

  a[0].tat = a[0].b; // first one doesn't wait so it's just a[0].b
  a[0].wt = 0; // first one doesn't wait at all
  a[0].ct = a[0].a + a[0].tat;

  wt_av = a[0].wt;
  tat_av = a[0].tat; // BASE CASE

	struct queue* qq = setup_queue(); 
  push(qq, 0);
  int* used = malloc(MAXN * sizeof(int)); // 1 if process has been used already, 0 if not yet
  while (!empty(qq))
  {
    int top_i = pop(qq); // index (inside array 'a') of the current process (the top one in the queue 'qq')
    struct P cur = a[top_i]; // the elem itself
    used[top_i] = 1; // mark that we've been here to not use it again in the future
    int min_b = INT_MAX, min_i = -1; // for min search
    for (int i = 0; i < n; i++) // find min burst time element entre those left
    {
      if (!used[i] && cur.ct >= a[i].a && a[i].b < min_b) // if burst times are equal then the first will be chosen as a[i].b < min_b is not strict
      {
        min_b = a[i].b; // update min
        min_i = i; // save the ind of the min process (burst-wise)
      }
    }
    if (min_i == -1) break; // if not found minimum process then we're outta processes
    a[min_i].ct = cur.ct + min_b; // goes right after current and burst time = min_b so it completes at time cur.ct+min_b
    a[min_i].wt = a[min_i].ct - (a[min_i].a + a[min_i].b); // at + bt + wt = ct => wt = ct - (at + bt)
    a[min_i].tat = min_b + a[min_i].wt; // tat = bt + wt where bt = min_b, wt = a[min_i].wt
    wt_av += a[min_i].wt;
    tat_av += a[min_i].tat;
    push(qq, min_i); // its the next on the next iteration
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
    4 1 6 1 8 2 7 3 3
     */
  return 0;
}

