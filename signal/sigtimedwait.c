#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(){
  sigset_t set;
  struct timespec tv;

  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  if(sigprocmask(SIG_BLOCK, &set, NULL) <0){
    perror("sigprocmask error");
    return 1;
  }

  tv.tv_sec=5;
  tv.tv_nsec=0;

  write(1, "calling sigtimedwait\n", 21);
  
  if(sigtimedwait(&set, NULL, &tv) < 0){
    if(errno == EAGAIN){
      write(1, "time out\n", 9);
      return 0;
    }  
    perror("sigtimedwait error");
    return 1;
  }
  write(1, "\nsigtimedwait returns\n", 22);
  return 0;
}
