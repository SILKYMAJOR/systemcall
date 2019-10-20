#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
  int sock_fd;
  struct sockaddr_in sv_addr;
  ssize_t n;
  char buf[4096];

  if((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
    perror("socket error");
    return 1;
  }
 
  memset(&sv_addr, 0, sizeof sv_addr);
  sv_addr.sin_family = AF_INET;
  sv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  sv_addr.sin_port = htons(12345);

  printf("DEBUG: Family = %d\n", sv_addr.sin_family);
  printf("DEBUG: addr = %d\n", sv_addr.sin_addr.s_addr);
  printf("DEBUG: port = %d\n", sv_addr.sin_port);

  if(connect(sock_fd, (struct sockaddr *)&sv_addr, sizeof sv_addr) < 0){
    perror("connect error");
    return 1;
  }

  write(sock_fd, "Hello\n", 6);

  if((n = read(sock_fd, buf, sizeof buf)) < 0){
    perror("read error");
    return 1;
  }
  write(1, buf, n);

  if(shutdown(sock_fd, SHUT_RDWR) < 0){
    perror("shutdown error");
    return 1;
  }
  return 0;
}
