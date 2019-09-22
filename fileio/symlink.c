#include <unistd.h>
#include <stdio.h>

int main(){
  if(symlink("./file.txt", "symlink.txt") <0){
    perror("symlink error");
    return 1;
  }
  return 0;
}
