#include <stdio.h>

#if defined(__sun__) && defined(__svr4__)
#include <unstd.h>
#endif

#include <sys/stat.h>
#include <fcntl.h>

int main(){
  int dirfd;
  if((dirfd = open("./", O_RDONLY)) <0){
    perror("open error");
    return 1;
  }
  if(renameat(dirfd, "renamed.txt", dirfd, "renameat.txt") <0){
    perror("renameat error");
    return 1;
  }
  return 0;
}

