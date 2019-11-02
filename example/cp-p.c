#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int maini(int argc, char **argv){
  int fd_r, fd_w;
  ssize_t n;
  int err = 0;
  struct stat s_buf;
  struct timespec times[2];
  char buf[4096];

  if(argc != 3){
    fprintf(stderr, "Usage: %s source dest\n", argv[0]);
    return 1;
  }
  
  if((fd_r = open(argv[1], O_RDONLY)) < 0){
    perror("argv[1]");
    return 1;
  }

  if(fstat(fd_r, &s_buf < 0)){
    perror(argv[1]);
    return 1;
  }

  if((fd_w = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0){
    perror(argv[2]);
    return 1;
  }

  while((n = read(fd_r, buf, sizeof buf)) > 0){
    if(write(fd_w, buf, n) < 0){
      perror(argv[2]);
      return 1;
    }
  }
  
  if(n < 0){
    perror(argv[1]);
    return 1;
  }

  times[0] = s_buf.st_atim;
  times[1] = s_buf.st_mtim;

  if(futimens(fd_w, times)){
    perror(argv[2]);
    err = 1;
  }

  fchown(fd_w, s_buf.st_uid, s_buf.st_gid);

  if(fchmod(fd_w, s_buf.st_mode) < 0){
    perror(argv[2]);
    err = 1;
  }
  return err;
}
