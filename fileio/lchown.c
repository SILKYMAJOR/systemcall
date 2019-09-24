#include <unistd.h>
#include <stdio.h>

int main(){
  if(lchown("symlink.txt", 501, 20) <0){
    perror("lchown error");
    return 1;
  }
  return 0;
}
