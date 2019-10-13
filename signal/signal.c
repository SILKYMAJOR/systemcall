#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static void func_int(){
  write(2, "\nSIGINT\n", 8);
}

int main(){
  if(signal(SIGINT, func_int) == SIG_ERR){
    perror("signal");
    return 1;
  }
  sleep(60);
  return 0;
}
