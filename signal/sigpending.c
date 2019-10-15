#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);

  if(sigprocmask(SIG_BLOCK, &set, NULL) < 0){
    perror("sigprocmask error");
    return 1;
  }

  write(1, "block SIGINT\n", 13);
  sleep(5);

  if(sigpending(&set) < 0){
    perror("sigpending");
    return 1;
  }

  if(sigismember(&set, SIGINT)){
    write(1, "\nSIGINT is pending\n", 19);
  }else{ 
    write(1, "\nSIGINT is not pending\n", 23);
  }
  return 0;
}
