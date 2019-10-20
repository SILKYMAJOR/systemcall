#include <unistd.h>
#include <stdio.h>

int main(){
  char name[256];

  if(getdomainname(name, sizeof name) < 0){
    perror("gerdomainname error");
    return 0;
  }
  printf("%s\n", name);
  return 0;
}
