#include <time.h>
#include <stdio.h>

int main(){
  time_t t;

  if((t = time(NULL)) < 0){
    perror("time error");
    return 1;
  }
  printf("%s", ctime(&t));
  return 0;
}
