#include "user/user.h"

int main(int argc, char *argv[]) {
  int pp[2][2];
  pipe(pp[0]);
  pipe(pp[1]);
  int pid = fork();
  char buf[16];
  if (pid < 0) {
    fprintf(2, "fork failed\n");
    exit(1);
  } else if (pid == 0) {
    close(pp[0][1]);
    close(pp[1][0]);
    read(pp[0][0], buf, 1);
    fprintf(1, "%d: received ping\n", getpid());
    write(pp[1][1], "1", 1);
    close(pp[0][0]);
    close(pp[1][1]);
  } else {
    close(pp[0][0]);
    close(pp[1][1]);
    write(pp[0][1], "1", 1);
    read(pp[1][0], buf, 1);
    fprintf(1, "%d: received pong\n", getpid());
    close(pp[0][1]);
    close(pp[1][0]);
  }
  exit(0);
}
