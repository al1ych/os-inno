#include "stdio.h"
#include "string.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int main()
{
  // originally in ex1.txt: "Hola! Todo bien?" (no quotation signs)
  int f = open("ex1.txt", O_RDWR);
  if (f < 0)
    printf("Error: cannot open file (or something with the file)"); 
  struct stat fs = {};
  if (fstat(f, &fs))
    printf("Error: meta");
  int size = fs.st_size;
  char *new_s = "Ten un buen dia!"; // Have a nice day! :)
  char *s = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);
  if (s == MAP_FAILED)
    printf("Error: mmap ");
  for (int i = 0; i < 16; i++)
    s[i] = new_s[i];
}
