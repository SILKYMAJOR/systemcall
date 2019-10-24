#include <time.h>
#include <stdio.h>

int main(){
  time_t t;
  struct tm tm;

  tm.tm_sec = 0;
  tm.tm_min = 0;
  tm.tm_hour = 0;
  tm.tm_mday = 1;
  tm.tm_mon = 0;
  tm.tm_year = 138;
  tm.tm_isdst = 0;
  t = mktime(&tm);
 
  if(stime(&t) < 0){
    perror("stime error");
    return 1;
  }
  return 0; 
}
