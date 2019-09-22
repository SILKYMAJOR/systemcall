#include <sys/stat.h>
#include <stdio.h>

int main(){
  if(mkdir("tmpdir", 0777) <0){
    perror("mkdir error");
    return 1;
  }
  return 0;
}
