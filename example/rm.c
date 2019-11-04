#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
  int i;
  int err = 0;

  if(argc <= 1){
    fprintf(stderr, "Usage: %s file ....\n", argv[0]);
    return 1;
  }

  for(i=1;i<argc;i++){
    if(unlink(argv[i]) < 0){
      perror(argv[i]);
      err = 1;
    }
  }
  return err;
}
