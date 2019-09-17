#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
  int fd;

  if((fd = open("/usr/bin", O_RDONLY)) < 0){
    perror("open error");
    return 1;
  }
  
  if(fchdir(fd)<0){
    perror("fchdir error");
    return 1;
  }
  system("pwd");
  return 0;
}
