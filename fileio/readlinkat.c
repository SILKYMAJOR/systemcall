#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int dirfd;
  ssize_t n;
  char buf[4096];

  if((dirfd = open("./", O_RDONLY))<0){
    perror("open error");
    return 1;
  }
  if((n = readlinkat(dirfd, "symlinkat.txt", buf, sizeof buf -1)) <0){
    perror("readlinkat error");
    return 1;
  }
  buf[n] = '\0';
  printf("%s\n", buf);
  return 0;
}
