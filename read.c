#include <unistd.h>
#include <stdio.h>

int main(){
  ssize_t n;
  char buf[4096];
  
  if((n = read(0, buf, sizeof buf)) < 0){
    perror("read error");
    return 1;
  }
  write(1, buf, n);
  return 0;
}
