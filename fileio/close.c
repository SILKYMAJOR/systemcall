#include <unistd.h>
#include <stdio.h>

int main(){
  if(close(1) <0){
    perror("close error");
    return 1;
  }

  return 0;

}
