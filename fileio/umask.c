#include <sys/stat.h>
#include <stdio.h>

int main(){
  mode_t u;
  u = umask(0);
  umask(u);

  printf("umask = %03o\n", u);
  return 0;

}
