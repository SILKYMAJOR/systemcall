#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

int main(){
  struct stat buf;
  char tim[256];
  if(stat("symlink.txt", &buf) <0){
    perror("stat error");
    return 1;
  }
  // Linux
  // strftime(tim, sizeof tim, "%Y-%m-%d %H:%M:%S", localtime(&buf.st_mtim.tv_sec));
  // printf("%s.%09ld\n", tim, buf.st_mtim.tv_nsec);
  
  // Mac
  strftime(tim, sizeof tim, "%Y-%m-%d %H:%M:%S", localtime(&buf.st_mtimespec.tv_sec));
  printf("%s.%09ld\n", tim, buf.st_mtimespec.tv_nsec);
  return 0;
}
