#include "user/user.h"

const int IT_MAX = 35;

void primes(int pr) {
  int first;
  int buf;
  int p[2];
  if (read(pr, &first, sizeof(first)) == 0) {
    close(pr);
    return;
  }
  printf("prime %d\n", first);
  pipe(p);
  if (fork()) {
    close(p[0]);
    while (read(pr, &buf, sizeof(buf))) {
      if (buf % first != 0) {
        write(p[1], &buf, sizeof(buf));
      }
    }
    close(p[1]);
  } else {
    close(p[1]);
    primes(p[0]);
  }
  close(pr);
}

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);
  int i = 2;
  if (fork()) {
    close(p[0]);
    while (i <= IT_MAX) {
      write(p[1], &i, sizeof(i));
      i++;
    }
    close(p[1]);
  } else {
    close(p[1]);
    primes(p[0]);
  }
  wait(0);
  exit(0);
}
