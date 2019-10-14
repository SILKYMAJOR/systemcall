#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static void func_int(){
  write(2, "\nnSIGINT\n", 8);
}

int main(){
  struct sigaction act;
  sigset_t set, oldset;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  if(sigprocmask(SIG_BLOCK, &set, &oldset) < 0){
    perror("sigprocmask error");
    return 1;
  }
  memset(&act, 0, sizeof act);
  act.sa_handler = func_int;
  if(sigaction(SIGINT, &act, NULL) < 0){
    perror("sigaction error");
    return 1;
  }
  write(1, "calling sigsuspend\n", 19);
  sigsuspend(&oldset);
  write(1, "sigsuspend returns\n", 19);
  return 0;
}
