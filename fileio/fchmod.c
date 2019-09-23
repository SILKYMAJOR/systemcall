#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int fd;
  if((fd = open("file.txt", O_RDONLY)) <0){
    perror("open error");
    return 1;
  }
  if(fchmod(fd, 0770) <0){
    perror("fchmod error");
    return 1;
  }
  return 0;
}
