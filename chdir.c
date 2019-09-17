#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  if(chdir("../")<0){
    perror("chdir error");
    return 1;
  }
  system("pwd");
  return 0;
}
