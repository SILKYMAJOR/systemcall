#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
  int sock_fd, ac_fd;
  struct sockaddr_in sv_addr, cl_addr;
  socklen_t cl_len;
  int optval;
  socklen_t optlen;
  ssize_t n;
  char buf[4096];

  if((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
    perror("socket error");
    return 1;
  }
  
  optval = 1;

  if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval) < 0){
    perror("setsocketopt error");
    return 1;
  }
  
  optlen = sizeof optval;

  if(getsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, &optlen) < 0){
    perror("getsocketopt error");
    return 1;
  }
  
  fprintf(stderr, "DEBUG: sock_fd = %d\n", sock_fd);
  fprintf(stderr, "DEBUG: SO_REUSEADDR = %d\n", optval);

  memset(&sv_addr, 0, sizeof sv_addr);
  sv_addr.sin_family = AF_INET;
  sv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  sv_addr.sin_port = htons(12345);

  if(bind(sock_fd, (struct sockaddr *)&sv_addr, sizeof sv_addr) < 0){
    perror("bind error");
    return 1;
  }
  
  if(listen(sock_fd, SOMAXCONN) < 0){
    perror("listen");
    return 1;
  }

  cl_len = sizeof cl_addr;

  if((ac_fd = accept(sock_fd, (struct sockaddr *)&cl_addr, &cl_len)) < 0){
    perror("accept error");
    return 1;
  }

  fprintf(stderr, "DEBUG: ac_fd = %d\n", ac_fd);
  
  fprintf(stderr, "[*] connect from addr = %s, port = %d\n", 
          inet_ntoa(cl_addr.sin_addr), ntohs(cl_addr.sin_port));

  while((n = read(ac_fd, buf, sizeof buf)) > 0){
    write(ac_fd, buf, n);
    write(1, buf, n);
  }
  
  if(n < 0){
    perror("read");
    return 1;
  }
  
  if(shutdown(ac_fd, SHUT_RDWR) < 0){
    perror("shutdown");
    return 1;
  }
  return 0;
}
