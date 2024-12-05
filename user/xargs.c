#include "user/user.h"

const int BUF_MAX = 512;

int main(int argc, char *argv[]) {
  char ind[1];
  char buf[BUF_MAX];
  char *buf_curr = buf;
  char *args[argc];
  for (int i = 1; i < argc; ++i) {
    args[i - 1] = argv[i];
  }
  args[argc - 1] = buf;
  while (read(0, ind, 1) > 0) {
    if (ind[0] == '\n') {
      *buf_curr++ = '\0';
      if (fork() == 0) {
        exec(argv[1], args);
      } else {
        wait(0);
        buf_curr = buf;
      }
    } else {
      *buf_curr++ = ind[0];
    }
  }
  exit(0);
}
