#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
  int sock_fd;
  struct addrinfo hints, *res;
  int err;
  fd_set readfds;
  ssize_t n;
  char buf[4096];

  if(argc != 3){
    fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
    return 1;
  }
  
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if((err = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0){
    fprintf(stderr, "%s %s: %s\n", argv[1], argv[2], gai_strerror(err));
    return 1; 
  }

  if((sock_fd = socket(res->ai_family, res->ai_socktype, 0)) < 0){
    perror("socket error");
    return 1;
  }

  if(connect(sock_fd, res->ai_addr, res->ai_addrlen) < 0){
    perror("connect error");
    return 1;
  }

  for(;;){
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(sock_fd, &readfds);

    if(select(sock_fd + 1, &readfds, NULL, NULL, NULL) < 0){
      perror("select error");
      return 1;
    }
    if(FD_ISSET(0, &readfds)){
      if((n = read(0, buf, sizeof buf)) < 0){
        perror("read error");
        return 1;
      }
      if(n ==0){
        break;
      }
      write(1, buf, n);
    }
  }
  if(shutdown(sock_fd, SHUT_RDWR) < 0){
    perror("shutdown");
    return 1;
  }
  return 0;
}
