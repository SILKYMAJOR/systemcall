#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int dirfd;
  int fd;
  if((dirfd = open("./", O_RDONLY)) < 0){
    perror("dirfd open error");
    return 1;
  }
  if((fd = openat(dirfd, "test.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666))<0){
    perror("fd openat error");
    return 1;
  }
  
  return 0;
}
