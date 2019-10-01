#include <utime.h>
#include <time.h>
#include <stdio.h>

int main(){
  struct utimbuf buf;
  struct tm t;

  t.tm_sec = 7;
  t.tm_min = 14;
  t.tm_hour = 12;
  t.tm_mday = 19;
  t.tm_mon = 0;
  t.tm_year = 138;
  t.tm_isdst = 0;
  buf.actime = mktime(&t);
  buf.modtime = buf.actime;

  if(utime("file.txt", &buf) <0){
    perror("utime error");
    return 1;
  }
  return 0;
}
