#include <unistd.h>
#include <stdio.h>

int main(){
  ssize_t n;

  if((n = write(1, "Hello\n", 6))<0){
    perror("write error");
    return 1;
  }

  return 0;
}
