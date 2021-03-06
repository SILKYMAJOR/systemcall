#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

int main(){
  int fd;
  struct stat buf;
  char tim[256];

  if((fd =open("file.txt", O_RDONLY)) <0){
    perror("open error");
    return 1;
  }
  if(fstat(fd, &buf) <0){
    perror("fstat error");
    return 1;
  }
  strftime(tim, sizeof tim, "%Y-%m-%d %H:%M:%S", localtime(&buf.st_mtimespec.tv_sec));
  printf("%s.%09ld\n", tim, buf.st_mtimespec.tv_nsec);
  return 0;

}
