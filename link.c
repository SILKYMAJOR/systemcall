#include <unistd.h>
#include <stdio.h>

int main(){
  if(link("file.txt", "newlink.txt") <0){
    perror("link error");
    return 1;
  }
  return 0;
}
