#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
  char *s;
  if((s = sbrk(7)) == (void *)-1){
    perror("sbrk error");
    return 1;
  }
  strcpy(s, "Hello\n");
  write(1, s, 6);
  if(brk(s) < 0){
    perror("brk error");
    return 1;
  }
  return 0;
}
