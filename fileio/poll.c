#include <poll.h>
#include <stdio.h>

int main(){
  int n;
  struct pollfd fds[2];
  
  fds[0].fd = 0;
  fds[0].events = POLLIN;
  fds[1].fd = 4;
  fds[1].events = POLLIN;

  n = poll(fds, 2, 2500);

  if(n <0){
    perror("poll");
    return 1;
  }else if(n == 0){
    printf("time out\n");
  }else{
    if(fds[0].revents & (POLLERR|POLLHUP|POLLNVAL)){
      fprintf(stderr, "error fd = 0\n");
      return 1;
    }
    if(fds[0].revents & POLLIN){
      printf("input from fd = 0\n");
    }
    
    if(fds[1].revents & (POLLERR|POLLHUP|POLLNVAL)){
      fprintf(stderr, "error fd = 4\n");
      return 1;
    }
    if(fds[1].revents & POLLIN){
      printf("input from fd = 4\n");
    }
  }
  return 0;
}
