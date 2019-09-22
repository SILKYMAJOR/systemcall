#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int dirfd;
  if((dirfd = open("./", O_RDONLY))<0){
    perror("open error");
    return 1;
  }
  if(symlinkat("./file.txt", dirfd, "symlinkat.txt") <0){
    perror("symlinkat error");
    return 1;
  }
  return 0;
}
