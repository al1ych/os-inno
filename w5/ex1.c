#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

static void * thread_start(void *ind)
{
   printf("Hello world from thread #%d\n", *((int*)ind));
   return NULL;
}

int main(int argc, char *argv[])
{
   int opt, N = 8;
   pthread_t tid[N];

   for (int tnum = 0; tnum < N; tnum++)
   {
       printf("Thread started: %d\n", tnum);
       pthread_create(&tid[tnum], NULL, &thread_start, &tnum);
       pthread_join(tid[tnum], NULL);
   }

   exit(EXIT_SUCCESS);
}
