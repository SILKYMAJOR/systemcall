#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int fd;
  char *argv[3];

  extern char **environ;

  if((fd = open("dupfile.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666)) <0){
    perror("oepn error");
    return 1;
  }
  close(1);

  if(dup(fd) < 0){
    perror("dup error");
    return 1;
  }
  close(fd);

  argv[0] = "echo";
  argv[1] = "Hello";
  argv[2] = NULL;

  execve("/bin/echo", argv, environ);
  
  // Abnormal processing
  perror("execve error");
  return 1;

}
