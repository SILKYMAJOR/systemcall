#include <sys/time.h>
#include <time.h>
#include <stdio.h>

int main(){
  struct timeval tv;
  char buf[256];

  if(gettimeofday(&tv, NULL) < 0){
    perror("gettimeofday");
    return 1;
  }
  strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S", localtime(&tv.tv_sec));
  printf("%s.%06ld\n", buf, tv.tv_usec);
  return 0;
}
