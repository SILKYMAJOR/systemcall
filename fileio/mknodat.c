#include <sys/stat.h>
#ifdef __linux__
# include <sys/sysmacros.h>
#elif defined(__FreeBSD__)
# include <sys/types.h>
#elif defined(__sun__) && defined(__svr4__)
# include <sys/mkdev.h>
#endif
#include <fcntl.h>
#include <stdio.h>

int main(){
  int dirfd;
  if((dirfd = open("./", O_RDONLY)) < 0){
    perror("open error");
    return 1;
  }
  if(mknodat(dirfd, "device", S_IFCHR|0666, makedev(1,3)) <0){
    perror("mknodat error");
    return 1;
  }
  return 0;
}
