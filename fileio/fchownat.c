#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  int dirfd;

  if((dirfd=open("./", O_RDONLY)) <0){
    perror("open error");
    return 1;
  }
  if(fchownat(dirfd, "symlink.txt", 501, 20, AT_SYMLINK_NOFOLLOW) <0){
    perror("fchownat error");
    return 1;
  }
  return 0;
}
