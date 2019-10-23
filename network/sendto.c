#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(){
  int sock_fd;
  struct sockaddr_in sv_addr;
  ssize_t n;

  if((sock_fd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
    perror("socket error");
    return 1;
  }

  memset(&sv_addr, 0, sizeof sv_addr);
  sv_addr.sin_family = AF_INET;
  sv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  sv_addr.sin_port = htons(12345);

  if((n = sendto(sock_fd, "Hello\n", 6, 0, (struct sockaddr *)&sv_addr, sizeof sv_addr)) < 0){
    perror("sendto");
    return 1;
  }
  return 0;
}
