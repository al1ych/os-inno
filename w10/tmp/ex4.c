#include "stdio.h"
#include "sys/stat.h"
#include "unistd.h"
#include "string.h"
#include "dirent.h"

int main (void)
{
  struct dirent *file;
  struct stat stat;
  freopen("ex4.txt", "w", stdout);

  DIR *d = opendir(".");
  if (!d)
  {
    printf("An error occured");
    return 0;
  }

  chdir(".");
  while ((file = readdir(d)))
  {
    lstat(file->d_name, &stat);
    if (strcmp(".", file->d_name) &&
        strcmp("..", file->d_name) &&
        stat.st_nlink >= 2)
      printf("%s\n", file->d_name);
  }
  chdir("..");
  closedir(d);

  return 0;
}
