#include <unistd.h>
#include <stdio.h>

int main(){
  int pipe_fd[2];
  ssize_t n;
  pid_t child_pid;
  char buf[4096];
  
  if(pipe(pipe_fd) < 0){
    perror("pipe error");
    return 1;
  }

  printf("pipe_fd[0] = %d\n", pipe_fd[0]);
  printf("pipe_fd[1] = %d\n", pipe_fd[1]);

  if((child_pid = fork()) < 0){
    perror("fork error");
    return 1;
  }else if(child_pid == 0){
    close(pipe_fd[0]);
    write(pipe_fd[1], "Hello\n", 6);
    _exit(0);
  }
  close(pipe_fd[1]);
  if((n = read(pipe_fd[0], buf, sizeof buf)) <0){
    perror("read error");
    return 1;
  }
  write(1, buf, n);
  return 0;
}
