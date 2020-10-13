#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

const int BUFFER_SIZE = 100;
const int PRINT_FREQ = 3;
int buf = 0;

pthread_t t_producer, t_consumer;
bool producer_enabled = 1, consumer_enabled = 0;

void * producer(void *arg)
{
  for (int i = 0; ; i++)
  {
    while (buf == BUFFER_SIZE);
    if (i % PRINT_FREQ == 0)
      printf("producer buffer %d\n", buf); 
    if (buf < BUFFER_SIZE)
    { 
      i++;
      buf++;
    }
  }
}

void * consumer(void *arg)
{
  for (int i = 0; ; i++)
  { 
    while (!buf); 
    if (i % PRINT_FREQ == 0)
      printf("consumer buffer %d\n", buf); 
    if (buf > 0)
    {
      i++;
      buf--;
    }
  }
}

int main()
{
  pthread_create(&t_producer, NULL, &producer, NULL);
  pthread_create(&t_consumer, NULL, &consumer, NULL);
  pthread_join(t_producer, NULL);
}

