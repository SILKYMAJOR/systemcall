#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
  int dirfd;

  if((dirfd = open("./", O_RDONLY)) < 0){
    perror("open error");
    return 1;
  }
  if(mkdirat(dirfd, "tmpdir", 0777) <0){
    perror("mkdirat");
    return 1;
  }
  return 0;
}
