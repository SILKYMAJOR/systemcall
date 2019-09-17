#include <unistd.h>
#include <stdio.h>

int main(){
  pid_t pid;
  
  if((pid=fork()) < 0){
    perror("fork error");
    return 1;
  }
  else if(pid==0){
    write(1, "child process\n", 14);
    _exit(0);
  }
  write(1, "parent process\n", 15);
  return 0;
}
