#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int dirfd;

  if((dirfd = open(".", O_RDONLY)) <0){
    perror("open error");
    return 1;
  }
  if(linkat(dirfd, "file.txt", dirfd, "newlink.txt", 0) <0){
    perror("linkat error");
    return 1;
  }
  return 0;
}
