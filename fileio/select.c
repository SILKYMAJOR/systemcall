#include <sys/select.h>
#include <stdio.h>
#if defined(__sun__) && defined(__svr4__)
#include <string.h>
#endif

int main(){
  int n;
  fd_set readfds;
  struct timeval tv;
  
  FD_ZERO(&readfds);
  FD_SET(0, &readfds);
  FD_SET(4, &readfds);

  tv.tv_sec = 2;
  tv.tv_usec = 500000;

  n = select(5, &readfds, NULL, NULL, &tv);

  if(n < 0){
    perror("select error");
    return 1;
  }else if(n == 0){
    printf("time out\n");
  }else{
    if(FD_ISSET(0, &readfds)){
      printf("input from fd = 0\n");
    }
    if(FD_ISSET(4, &readfds)){
      printf("input from fd = 4\n");
    } 
  }
  return 0;
}
