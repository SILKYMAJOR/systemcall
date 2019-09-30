#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  int fd;
  struct flock lock;

  if((fd = open("fcntl.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0){
    perror("open error");
    return 1;
  }
  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_CUR;
  lock.l_start = 0;
  lock.l_len = 0;

  if(fcntl(fd, F_SETLKW, &lock) <0){
    perror("fcntl lock error");
    return 1;
  }
  printf("F_SETLKW sleep 15 sec\n");
  sleep(15);
  return 0;
}
