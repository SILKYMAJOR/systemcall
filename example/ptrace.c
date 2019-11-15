#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]){
  int pid, status, count =0;
  pid = fork();

  if(!pid){
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execve(argv[1], argv + 1, envp);
  }
  
  while(1){
    waitpid(pid, &status, 0);
    if(WIFEXITED(status))
      break;
    ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    count++;
  }
  fprintf(stderr, "COUNT: %d\n", count);
  exit(0);
}

