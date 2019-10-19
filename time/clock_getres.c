#include <time.h>
#include <stdio.h>

int main(){
  struct timespec tv;
  if(clock_getres(CLOCK_REALTIME, &tv) <0){
    perror("clock_getres error");
    return 1;
  }
  printf("%ld.%09lds\n", tv.tv_sec, tv.tv_nsec);
  return 0;
}
