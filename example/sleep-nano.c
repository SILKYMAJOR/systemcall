#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  struct timespec req;
  char *end;
  
  if(
    argc != 2 ||
    argv[1][0] == '\0' ||
    (req.tv_sec = strtol(argv[1], &end, 10), *end != '\0')
  ){
    fprintf(stderr, "Usage: %s seconds\n", argv[0]);
    return 1;
  }

  req.tv_nsec = 0;

  if(nanosleep(&req, NULL) < 0){
    perror("nanosleep");
    return 1;
  }
  return 0;
}
