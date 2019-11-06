#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <stdio.h>

int main(int argc, char **argv){
  int i;
  int fd;
  int err = 0;
  if(argc <= 1){
    fprintf(stderr, "Usage: %s file...\n", argv[0]);
    return 1;  
  }
  for(i=1;i<argc;i++){
    fd = open(argv[i], O_WRONLY|O_CREAT, 0666);
    if(fd >= 0){
      close(fd);
    }
    if(utime(argv[i], NULL)){
      perror(argv[i]);
      err=1;
    }
  }
  return err;
}
