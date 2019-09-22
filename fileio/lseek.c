#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int fd;
  off_t offset;
  ssize_t n;
  char buf[4096];

  if((fd = open("file.txt", O_RDONLY)) <0){
    perror("open error");
    return 1;
  }
  
  if((offset = lseek(fd, 7, SEEK_SET)) <0){
    perror("lseek error");
    return 1;
  }

  if((n = read(fd, buf, sizeof buf)) <0){
    perror("read error");
    return 1;
  }

  write(1, buf, n);
  return 0;
}
