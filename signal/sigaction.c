#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static void func_int(){
  write(2, "\nSIGINT\n", 8);
}

int main(){
  struct sigaction act;

  memset(&act, 0, sizeof act);
  act.sa_handler = func_int;
  if(sigaction(SIGINT, &act, NULL) < 0){
    perror("sigaction");
    return 1;
  }
  sleep(60);
  return 0;
}
