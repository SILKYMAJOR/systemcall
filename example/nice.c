#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int pri;
  char **com;
  char *end;

  errno = 0;
  pri = getpriority(PRIO_PROCESS, 0);
  
  if(errno != 0){
    perror("getpriority error");
    return 1;
  }

  if(argc <= 1){
    printf("%d\n", pri);
    return 0;
  }

  if(argv[1][0] == '-'){
    if(
      argc <= 2 ||
      argv[1][1] == '\0' ||
      (pri += strtol(&argv[1][1], &end, 10), *end != '\0')
    ){
      fprintf(stderr, "Usage: %s [-number] command [arg...]\n", argv[0]);
      return 1;
    }
    com = &argv[2];
  }else{
    pri += 10;
    com = &argv[1];
  }
  if(setpriority(PRIO_PROCESS, 0, pri) < 0){
    perror("setpriority error");
    return 1;
  }
  execvp(com[0], com);
  perror(com[0]);
  return 1;
}
