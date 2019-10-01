#include <sys/stat.h>
#ifdef __linux__
# include <sys/sysmacros.h>
#elif defined(__FreeBSD__)
# include <sys/types.h>
#elif defined(__sun__) && defined(__svr4__)
# include <sys/mkdev.h>
#endif
#include <stdio.h>

int main(){
  if(mknod("device", S_IFCHR|0666, makedev(1,3)) <0){
    perror("mknod error");
    return 1;
  }
  return 0;
}
