#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
  int fd_r, fd_w;
  ssize_t n;
  char buf[4096];

  if(argc != 3){
    fprintf(stderr, "Usage: %s source dest\n", argv[0]);
    return 1;
  }

  if((fd_r = open(argv[1], O_RDONLY)) < 0){
    perror("open error : read");
    return 1;
  }

  if((fd_w = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0){
    perror("open error : write");
    return 1;
  }

  while((n = read(fd_r, buf, sizeof buf)) > 0){
    if(write(fd_w, buf, n) < 0){
      perror("write error");
      return 1;
    }
  }
  
  if(n < 0){
    perror(argv[1]);
    return 1;
  }
  return 0;
}
