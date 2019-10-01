#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  int fd;
  char *argv[3];
  extern char **environ;

  if((fd = open("fcntl.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0){
    perror("open error");
    return 1;
  }
  close(1);

  if(fcntl(fd, F_DUPFD, 1) <0){
    perror("fcntl error");
    return 1;
  }
  close(fd);

  argv[0] = "echo";
  argv[1] = "fnctl";
  argv[2] = NULL;
  execve("/bin/echo", argv, environ);

  perror("execve error");
  return 1;
}
