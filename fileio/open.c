#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int fd_r, fd_w;

  if((fd_r = open("./README.md", O_RDONLY))<0){
    perror("open r error");
    return 1;
  }

  if((fd_w = open("file.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666))<0){
    perror("open w error");
    return 1;
  }

}
