#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

int main(){
  struct stat buf;
  char tim[256];

  if(lstat("symlink.txt", &buf) <0){
    perror("lstat error");
    return 1;
  }
  strftime(tim, sizeof tim, "%Y-%m-%d %H:%M:%S", localtime(&buf.st_mtimespec.tv_sec));
  printf("%s.%09ld\n", tim, buf.st_mtimespec.tv_nsec);
  return 0;

}
