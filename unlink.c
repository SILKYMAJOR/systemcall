#include <unistd.h>
#include <stdio.h>

int main(){
  if(unlink("newlink.txt") <0){
    perror("unlink error");
    return 1;
  }
  return 0;
}
