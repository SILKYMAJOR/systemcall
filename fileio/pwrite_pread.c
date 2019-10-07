#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int fd_r, fd_w;
  ssize_t n;
  char buf[256];

  if((fd_r = open("file1.txt", O_RDONLY)) < 0){
    perror("open error");
    return 1;
  }
  if((fd_w = open("file2.txt", O_WRONLY|O_CREAT, 0666)) < 0){
    perror("open error");
    return 1;
  }
  if((n=pread(fd_r, buf, sizeof buf, 10)) < 0){
    perror("pread error");
    return 1;
  }
  if(pwrite(fd_w, buf, n, 10) < 0){
    perror("pwrite error");
    return 1;
  }
  return 0;
}
