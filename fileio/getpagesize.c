#include <unistd.h>
#include <stdio.h>

int main(){
  int s;
  s = getpagesize();
  printf("pagesize = %d\n", s);
  return 0; 
}
