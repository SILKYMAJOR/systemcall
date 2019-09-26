#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  int dirfd;

  if((dirfd = open("./", O_RDONLY)) < 0){
    perror("open error");
    return 1;
  }
  if(faccessat(dirfd, "file.txt", R_OK|X_OK, AT_EACCESS) <0){
    perror("faccessat error");
    return 1;
  }
  printf("access OK\n");
  return 0;
}
