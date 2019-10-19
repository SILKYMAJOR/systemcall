#include <time.h>
#include <stdio.h>

int main(){
  struct timespec tv;
  char buf[256];

  if(clock_gettime(CLOCK_REALTIME, &tv) < 0){
    perror("clock_gettime error");
    return 1;
  }
  strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S", localtime(&tv.tv_sec));
  printf("%s.%09ld\n", buf, tv.tv_nsec);
  return 0;
}
