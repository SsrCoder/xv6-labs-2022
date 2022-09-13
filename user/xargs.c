#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

const int MAXLEN = 1000;

void run(int argc, char *args[])
{
  if (fork() == 0)
  {
    exec(args[0], args);
    exit(0);
  }
  else
  {
    wait(0);
  }
}

int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    fprintf(2, "Usage: xargs cmd param...\n");
    exit(1);
  }

  if (argc > MAXARG)
  {
    fprintf(2, "over max args...\n");
  }

  char buf[MAXLEN];
  int n;
  char *args[argc];
  for (int i = 1; i < argc; i++)
  {
    args[i - 1] = argv[i];
  }

  char word[MAXLEN];
  char *wordP = word;

  while ((n = read(0, buf, sizeof(buf))) > 0)
  {
    for (int i = 0; i < n; i++)
    {
      switch (buf[i])
      {
      case '\n':
        *wordP = '\0';
        args[argc - 1] = word;
        run(argc, args);
        wordP = word;
        break;
      default:
        if (wordP - word >= MAXLEN)
        {
          fprintf(2, "over max len...\n");
        }
        *wordP = buf[i];
        wordP++;
        break;
      }
    }
  }

  exit(0);
}
