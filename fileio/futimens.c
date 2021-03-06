#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

int main(){
  struct timespec times[2];
  struct tm t;
  int fd;

  if((fd = open("file.txt", O_RDONLY)) <0){
    perror("open error");
    return 1;
  }
  
  t.tm_sec = 7;
  t.tm_min = 14;
  t.tm_hour = 12;
  t.tm_mday = 19;
  t.tm_mon = 0;
  t.tm_year = 138;
  t.tm_isdst = 0;
  times[0].tv_sec = mktime(&t);
  times[0].tv_nsec = 987654321;
  times[1] = times[0]; 

  if(futimens(fd, times) <0){
    perror("futimens");
    return 1;
  }
  return 0;
}
