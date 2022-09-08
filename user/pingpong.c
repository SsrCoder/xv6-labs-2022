#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int p[2];

  pipe(p);

  if (fork() == 0)
  {
    // child
    read(p[0], (char *)0, 1);
    printf("%d: received ping\n", getpid());
    write(p[1], (char *)0, 1);
  }
  else
  {
    // parent
    write(p[1], (char *)0, 1);
    read(p[0], (char *)0, 1);
    printf("%d: received pong\n", getpid());
  }

  exit(0);
}
