#include <unistd.h>
#include <stdio.h>

int main(){
  if(rmdir("tmpdir") <0){
    perror("rmdir error");
    return 1;
  }
  return 0;
}
