#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int dirfd;
  if((dirfd = open("./", O_RDONLY)) <0){
    perror("open error");
    return 1;
  }
  if(fchmodat(dirfd, "file.txt", 0750, 0) <0){
    perror("fchmodat error");
    return 1;
  }
  return 0;
}
