#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
  int status;
  pid_t pid;
  struct rusage usage;
  struct timeval tv_start, tv_end;

  if(argc <= 1){
    fprintf(stderr, "Usage: %s command [arg...]\n", argv[0]);
    return 1;
  }
  if(gettimeofday(&tv_start, NULL) < 0){
    perror("gettimeofday error");
    return 1;
  }
  if((pid = fork()) < 0){
    perror("fork error");
    return 1;
  }else if(pid == 0){
    execvp(argv[1], &argv[1]);
    perror(argv[1]);
    _exit(1);
  }
  
  if(wait3(&status, 0, &usage) < 0){
    perror("wait3 error");
    return 1;
  }
  
  if(gettimeofday(&tv_end, NULL) < 0){
    perror("gettimeofday error");
    return 1;
  }

  tv_end.tv_sec -= tv_start.tv_sec;
  if((tv_end.tv_usec -= tv_start.tv_usec) < 0){
    tv_end.tv_sec--;
    tv_end.tv_usec += 1000000;
  }
  fprintf(
     stderr,
     "real    = %ld.%06ld\n"
     "user    = %ld.%06ld\n"
     "system  = %ld.%06ld\n",
     tv_end.tv_sec, tv_end.tv_usec,
     usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
     usage.ru_stime.tv_sec, usage.ru_stime.tv_usec
  );

  if(WIFEXITED(status)){
    return WEXITSTATUS(status);
  }
  return 1;

}
