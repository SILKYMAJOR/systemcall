#include <time.h>
#include <stdio.h>

int main(){
  struct timespec tv;
  struct tm tm;

  tm.tm_sec = 0;
  tm.tm_min = 0;
  tm.tm_hour = 0;
  tm.tm_mday = 1;
  tm.tm_mon = 0;
  tm.tm_year = 0;
  tm.tm_isdst = 0;

  tv.tv_sec = mktime(&tm);
  tv.tv_nsec = 0;

  if(clock_settime(CLOCK_REALTIME, &tv) < 0){
    perror("clock_settime error");
    return 1;
  }
  return 0;
}
