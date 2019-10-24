#include <unistd.h>
#include <stdio.h>

int main(){
  ssize_t n;
  char buf[4096];

  while((n = read(0, buf, sizeof buf)) > 0){
    if(write(1, buf, n) < 0){
      perror("write");
      return 1;
    }
  }
  if(n < 0){
    perror("read");
    return 1;
  }
  return 0;
}
