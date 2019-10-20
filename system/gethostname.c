#include <unistd.h>
#include <stdio.h>

int main(){
  char name[256];
  if(gethostname(name, sizeof name) < 0){
    perror("gethostname error");
    return 1;
  }
  printf("%s\n", name);
  return 0;
}
