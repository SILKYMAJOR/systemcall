#include <unistd.h>
#include <stdio.h>

int main(){
  if(chown("file.txt", 501, 20) <0){
    perror("chown error");
    return 1;
  }
  return 0;
}
