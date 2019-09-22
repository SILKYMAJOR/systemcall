#include <unistd.h>
#include <stdio.h>

int main(){
  ssize_t n;
  char buf[4096];

  if((n = readlink("symlink.txt", buf, sizeof buf -1)) <0){
    perror("readlink error");
    return 1;
  }
  buf[n] = '\0';
  printf("%s\n", buf);
  return 0;
}
