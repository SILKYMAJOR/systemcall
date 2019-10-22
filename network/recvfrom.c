#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
  int sock_fd;
  struct sockaddr_in sv_addr, cl_addr;
  socklen_t cl_len;
  ssize_t n;
  char buf[4096];
  
  if((sock_fd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
    perror("socket error");
    return 1;
  }

  memset(&sv_addr, 0, sizeof sv_addr);
  sv_addr.sin_family = AF_INET;
  sv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  sv_addr.sin_port = htons(12345);

  if(bind(sock_fd, (struct sockaddr *)&sv_addr, sizeof sv_addr) < 0){
    perror("bind error");
    return 1;
  }
  
  cl_len = sizeof cl_addr;

  if((n = recvfrom(sock_fd, buf, sizeof buf, 0, (struct sockaddr *)&cl_addr, &cl_len)) < 0){
    perror("recvfrom error");
    return 1;
  }

  fprintf(stderr, "UDP from addr = %s, port = %d\n", inet_ntoa(cl_addr.sin_addr), ntohs(cl_addr.sin_port));

  write(1, buf, n);
  return 0;

}

