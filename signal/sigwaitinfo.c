#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  if(sigprocmask(SIG_BLOCK, &set, NULL) <0){
    perror("sigprocmask error");
    return 1;
  }
  write(1, "calling sigwaitinfo\n", 20);
  if(sigwaitinfo(&set, NULL) < 0){
    perror("sigwaitinfo error");
    return 1;
  }
  write(1, "\nsigwaitinfo returns\n", 21);
  return 0;
}
