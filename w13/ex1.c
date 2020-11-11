#include <stdio.h>
#include <stdbool.h>

int main()
{
  freopen("input_ok.txt", "r", stdin); // "input_dl" or "input_ok"

  int rsrc_cnt; scanf("%i", &rsrc_cnt);
  int proc_cnt; scanf("%i", &proc_cnt);

  int E[rsrc_cnt];
  int A[rsrc_cnt];

  for (int i = 0; i < rsrc_cnt; i++) scanf("%i ", &E[i]);
  for (int i = 0; i < rsrc_cnt; i++) scanf("%i ", &A[i]);

  int aloc[proc_cnt][rsrc_cnt];
  for (int i = 0; i < proc_cnt; i++)
    for (int j = 0; j < rsrc_cnt; j++)
      scanf("%i ", &aloc[i][j]);

  int req[proc_cnt][rsrc_cnt];
  bool done[proc_cnt];
  for (int i = 0; i < proc_cnt; i++)
  {
    done[i] = false;
    for (int j = 0; j < rsrc_cnt; j++)
      scanf("%i ", &req[i][j]);
  }


  int dls = 0; // deadlocks
  for (int done_cnt = 0; done_cnt != proc_cnt; done_cnt++, dls++)
  {
    for (int i = 0; i < proc_cnt; i++)
    {
      bool is_ex = true;
      for (int j = 0; j < rsrc_cnt; j++)
      {
        if (req[i][j] > A[j])
        {
          is_ex = false;
          break;
        }
      }

      if (is_ex && done[i] == false)
      {
        dls--;
        done[i] = true;
        for (int j = 0; j < rsrc_cnt; j++)
          A[j] += aloc[i][j];
      }
    }
  }

  if (dls)
  {
    freopen("output_dl.txt", "w", stdout);
    printf("Found deadlock procs: ");
    for (int i = 0; i < proc_cnt; i++)
      if (!done[i])
          printf("%i ", i + 1);

    freopen("output_ok.txt", "w", stdout);
    printf("Found deadlock procs: ");
    for (int i = 0; i < proc_cnt; i++)
      if (!done[i])
          printf("%i ", i + 1);
  }
  else
  {
    freopen("output_ok.txt", "w", stdout);
    printf("No deadlock is detected :<");

    freopen("output_dl.txt", "w", stdout);
    printf("No deadlock is detected :<");
  }
}
