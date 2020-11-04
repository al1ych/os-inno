#include "stdio.h"
#include "string.h"
#include "fcntl.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include <stdbool.h>

int main(int argc, char *argv[])
{
  int fcount = 0, files[argc];
  bool append_mode = 0;
  char c;
  if (argc >= 2)
    for (int i = 1; i < argc; i++)
      if (!strcmp(argv[i], "-a"))
        append_mode = true;
      else
        files[fcount++] = i;
  for (int i = 0; i < fcount; i++)
    if (append_mode == true)
      files[i] = open(argv[files[i]], O_RDWR | O_APPEND);
    else 
      files[i] = open(argv[files[i]], O_RDWR);
  files[fcount] = STDOUT_FILENO;
  while (read(STDIN_FILENO, &c, 1) > 0)
    for (int i = 0; i <= fcount; i++)
      write(files[i], &c, 1);
  for (int i = 0; i < fcount; i++)
    close(files[i]);
}
