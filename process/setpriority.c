#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  if(setpriority(PRIO_PROCESS, 0, 19) < 0){
    perror("setpriority error");
    return 1;
  }
  execl("./getpriority", "./getpriority", NULL);
  perror("execl error");

  return 1;
}
