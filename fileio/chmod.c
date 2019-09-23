#include <sys/stat.h>
#include <stdio.h>

int main(){
  if(chmod("file.txt", 0750) <0){
    perror("chmod error");
    return 1;
  }
  return 0;
}
