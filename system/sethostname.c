#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
  char name[] = "newname";
  if(sethostname(name, strlen(name)) < 0){
    perror("sethostname error");
    return 1;
  }
  return 0;
}
