#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
  char name[] = "nisdomain";

  if(setdomainname(name, strlen(name)) < 0){
    perror("setdomainname");
    return 1;
  }
  return 0;
}
