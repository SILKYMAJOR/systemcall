#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  int status;
  pid_t pid;

  if((pid=fork())<0){
    perror("fork error");
    return 1;
  }
  else if(pid == 0){
    write(1, "child process\n", 14);
    _exit(12);
  }

  write(1, "parent process\n", 15);

  if((pid = waitpid(pid, &status, 0)) < 0){
    perror("waitpid error");
    return 1;
  }
  if(WIFEXITED(status)){
    printf("pid=%d exited with status = %d\n", pid, WEXITSTATUS(status));
  }
  return 0;
}
