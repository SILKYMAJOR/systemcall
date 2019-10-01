#include <sys/time.h>
#include <time.h>
#include <stdio.h>

int main(){
  struct timeval times[2];
  struct tm t;

  t.tm_sec = 7;
  t.tm_min = 14;
  t.tm_hour = 12;
  t.tm_mday = 19;
  t.tm_mon = 0;
  t.tm_year = 138;
  t.tm_isdst = 0;
  times[0].tv_sec = mktime(&t);
  times[0].tv_usec = 123456;
  times[1] = times[0]; 

  if(utimes("file.txt", times) <0){
    perror("utimes error");
    return 1;
  }
  return 0;
}
