#include <unistd.h>
#include <stdio.h>

int main(){
  int s;

  s = getdtablesize();
  printf("getdtablesize() = %d\n", s);
  return 0;
}
