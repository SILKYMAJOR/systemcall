#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static int cat(int fd, char *file){
  ssize_t n;
  char buf[4096];

  while((n = read(fd, buf, sizeof buf)) > 0){
    if(write(1, buf, n) < 0){
      perror("write");
      return 1;
    }
  }
  if(n < 0){
    perror("read");
    return 1;
  }
  return 0;
}

int main(int argc, char **argv){
  int i;
  int fd;
  int err = 0;

  if(argc <= 1){
    return cat(0, "stdin");
  }
  for(i=1;i<argc;i++){
    if((fd = open(argv[i], O_RDONLY)) < 0){
      perror(argv[i]);
      err = 1;
      continue;
    }
    err |= cat (fd, argv[1]);
    if(close(fd) < 0){
      perror(argv[i]);
      err = 1;
    }
  }
  return err;
}
