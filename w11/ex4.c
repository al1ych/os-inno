#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/mman.h"
#include "stdlib.h"
#include "stdbool.h"

void ASSERT(bool x, int t)
{
  if (!x)
  {
    printf("Error! Cannot copy the content of the file! Error code: %i", t);
    exit(0);
  }
}

int main()
{
    char *A, *B;
    int Af, Bf; // file A, file B
    Af = open("ex1.txt", O_RDONLY);
    ASSERT(Af >= 0, 0); // errcode 0
    struct stat fs = {};
    ASSERT(!fstat(Af, &fs), 1); // errcode 1
    int size = fs.st_size;
    A = mmap(0, size, PROT_READ, MAP_PRIVATE, Af, 0);
    ASSERT(A != MAP_FAILED, 2); // errcode 2
    Bf = open("ex1.memcpy.txt", O_RDWR);
    ASSERT(Bf >= 0, 3); // errcode 3
    ASSERT(ftruncate(Bf, size) != -1, 4); // errcode 4
    B = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, Bf, 0);
    ASSERT(B != MAP_FAILED, 5); // errcode 5
    memcpy(B, A, size);
}
