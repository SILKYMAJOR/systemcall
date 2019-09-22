#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  int dirfd;
  if((dirfd = open("./", O_RDONLY)) <0){
    perror("open error");
    return 1;
  }
  if(unlinkat(dirfd, "newlink.txt", 0) <0){
    perror("unlinkat error");
    return 1;
  }
  return 0;
}
