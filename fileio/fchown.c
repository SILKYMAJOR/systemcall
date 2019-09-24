#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  int fd;

  if((fd=open("file.txt", O_RDONLY)) <0){
    perror("open error");
    return 1;
  }
  if(fchown(fd, 501, 20) <0){
    perror("fchown error");
    return 1;
  }
  return 0;
}
