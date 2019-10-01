#include <sys/file.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  int fd;
  if((fd = open("file.txt", O_WRONLY|O_CREAT, 0666))< 0){
    perror("open error");
    return 1;
  }
  if(flock(fd, LOCK_EX) <0){
    perror("flock error");
    return 1;
  }
  printf("flock\n");
  sleep(5);
  return 0;  
}
