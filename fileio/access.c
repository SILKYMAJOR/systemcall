#include <unistd.h>
#include <stdio.h>

int main(){
  if(access("file.txt", R_OK|X_OK) <0){
    perror("access error");
    return 1;
  }
  printf("access OK\n");
  return 0;
}
