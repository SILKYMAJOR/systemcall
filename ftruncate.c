#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int fd;

  if((fd = open("file.txt", O_WRONLY))<0){
    perror("open error");
    return 1;
  }
  if(ftruncate(fd, 9)<0){
    perror("ftruncate error");
    return 1;
  }
  return 0;

}
