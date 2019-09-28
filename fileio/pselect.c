#include <sys/select.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#if defined(__sun__) && defined(__svr4__)
#include <string.h>
#endif

static int sigint_flag;

static void func_int(){
  sigint_flag = 1;
}

int main(){
  int n;
  fd_set readfds;

  struct timespec tv;
  sigset_t mask, unmask;
  
  if(sigprocmask(SIG_BLOCK, &mask, &unmask) < 0){
    perror("sigprocmask error");
    return 1;
  }
  signal(SIGINT, func_int);

  FD_ZERO(&readfds);
  FD_SET(0, &readfds);
  FD_SET(4, &readfds);

  tv.tv_sec = 2;
  // timeout 0.5sec
  tv.tv_nsec = 500000000;

  n = pselect(5, &readfds, NULL, NULL, &tv, &unmask);

  if(n < 0){
    if(errno == EINTR && sigint_flag){
      printf("\nreceive SIGINT\n");
      return 0;
    }
    perror("pselect error");
    return 1;
  }else if(n == 0){
    printf("time out\n");
  }else{
    if(FD_ISSET(0, &readfds)){
      printf("input from fd = 0\n");
    }
    if(FD_ISSET(4, &readfds)){
      printf("input from fd = 4\n");
    } 
  }
  return 0;
}
