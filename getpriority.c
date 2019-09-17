#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <stdio.h>

int main(){
  int pri;
  errno = 0;
  pri = getpriority(PRIO_PROCESS, 0);
  
  if(errno != 0){
    perror("getpriority error");
    return 1;
  }
  printf("%d\n", pri);
  return 0;
}

