#include <unistd.h>
#include <stdio.h>

int main(){

  if(truncate("file.txt", 10) < 0){
    perror("truncate error");
    return 1;
  }
  return 0;
}
