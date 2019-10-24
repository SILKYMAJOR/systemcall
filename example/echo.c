#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
  int i;
  if(argc >= 2){
    for(i = 1;;){
      write(1, argv[i], strlen(argv[i]));
      if(++i >= argc){
        break;
      }
      write(1, " ", 1);
    }
  }
  write(1, "\n", 1);
  return 0;
}
