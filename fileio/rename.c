#include <stdio.h>

int main(){
  if(rename("renamefile.txt", "renamed.txt") <0){
    perror("rename error");
    return 1;
  }
  return 0;
}
