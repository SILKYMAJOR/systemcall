#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  struct timeval tv;
  char *end;

  if(
    argc != 2 ||
    argv[1][0] == '\0' ||
    (tv.tv_sec = strtol(argv[1], &end, 10), *end != '\0')
  ){
    fprintf(stderr, "Usage: %s seconds\n", argv[0]);
    return 1;
  }

  tv.tv_usec = 0;

  if(select(0, NULL, NULL, NULL, &tv) < 0){
    perror("select");
    return 1;
  }

  return 0;
}
