#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  pid_t pid;
  pid = 0;
  if(argc >=2){
    pid = atoi(argv[1]);
  }
  if(kill(pid, SIGTERM) <0){
    perror("kill error");
    return 1;
  }
  return 0;
}
