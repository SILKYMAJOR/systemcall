#include <time.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>

static void func(){
  printf("signal\n");
}

int main(){
  struct timespec req, rem;
  if(signal(SIGINT, func) == SIG_ERR){
    perror("signal");
    return 1;
  }
  req.tv_sec = 2;
  req.tv_nsec = 500000000;
  while(nanosleep(&req, &rem) < 0){
    if(errno == EINTR){
      printf(" - remain %ld.%09lds\n", rem.tv_sec, rem.tv_nsec);
      req = rem;
      continue;
    }
    perror("nanosleep error");
    return 1;
  }
  return 0;
}
