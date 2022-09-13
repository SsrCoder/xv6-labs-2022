#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void receive(int in)
{
  int p[2];
  pipe(p);
  if (fork() == 0)
  {
    // child
    close(p[1]);
    receive(p[0]);
    close(p[0]);
  }
  else
  {
    // parent
    close(p[0]);
    char first = 0;
    char i;
    while (read(in, &i, sizeof(char)) > 0)
    {
      if (first == 0)
      {
        first = i;
        printf("prime %d\n", first);
      }
      else if (i % first != 0)
      {
        write(p[1], &i, sizeof(char));
      }
    }
    close(p[1]);
    wait(0);
  }

  exit(0);
}

int main(int argc, char *argv[])
{
  int p[2];

  pipe(p);

  if (fork() == 0)
  {
    // child
    close(p[1]);
    receive(p[0]);
    close(p[0]);
  }
  else
  {
    // parent
    close(p[0]);
    for (char i = 2; i < 32; i++)
    {
      write(p[1], &i, sizeof(char));
    }
    close(p[1]);
    wait(0);
  }

  exit(0);
}
