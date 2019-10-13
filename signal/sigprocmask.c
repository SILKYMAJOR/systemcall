#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  sigset_t set, oldset;
  
  sigemptyset(&set);
  sigaddset(&set, SIGINT);

  if(sigprocmask(SIG_BLOCK, &set, &oldset) < 0){
    perror("sigprocmask");
    return 1;
  }
  write(1, "block SIGINT\n", 13);
  sleep(5);
  write(1, "unblock SIGINT\n", 16);

  if(sigprocmask(SIG_SETMASK, &oldset, NULL) < 0){
    perror("sigprocmask");
    return 1;
  }
  sleep(5);
  return 0;
}
