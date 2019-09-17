#include <unistd.h>
#include <stdio.h>

int main(){
  if(chroot("/home") < 0){
    perror("chroot error");
    return 1;
  }
  if(chdir("/") < 0){
    perror("chdir error");
    return 1;
  }

  sleep(60);
  return 0;
}
