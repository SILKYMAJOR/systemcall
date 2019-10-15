#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  int signo;
  struct itimerval val;
  sigset_t set;

  sigemptyset(&set);
  sigaddset(&set, SIGALRM);
  sigaddset(&set, SIGINT);

  if(sigprocmask(SIG_BLOCK, &set, NULL) < 0){
    perror("sigprocmask error");
    return 1;
  }
  val.it_interval.tv_sec = 1;
  val.it_interval.tv_usec = 0;
  val.it_value = val.it_interval;

  if(setitimer(ITIMER_REAL, &val, NULL) < 0){
    perror("setitimer error");
    return 1;
  }
  if(getitimer(ITIMER_REAL, &val) < 0){
    perror("getitimer");
    return 1;
  }

  printf(
    "it_interval = %ld.%06ld\n"
    "it_value = %ld.%06ld\n",
    val.it_interval.tv_sec, val.it_interval.tv_usec,
    val.it_value.tv_sec, val.it_value.tv_usec
    );

  while((signo = sigwaitinfo(&set, NULL)) != SIGINT){
    if(signo < 0){
      perror("sigwaitinfo error");
      return 1;
    }
    if(signo == SIGALRM){
      write(1, ".", 1);
    }
  }
  write(1, "\nSIGINT\n", 8);
  return 0;
}
