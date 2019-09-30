#if defined(__sun__) && defined(__svr4__)
#include <unistd.h>
#define BSD_COMP
#endif

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(){
  struct ifconf ifc;
  struct ifreq ifrbuf[16];
  struct ifreq *ifrp;
  int sfd;
  int adj = 0;

  if((sfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
    perror("socket error");
    return 1;
  }

  ifc.ifc_req = ifrbuf;
  ifc.ifc_len = sizeof ifrbuf;
  
  if(ioctl(sfd, SIOCGIFCONF, &ifc) <0 ){
    perror("ioctl(SIOCGIFCONF) error");
    return 1;
  }

  for(ifrp=ifrbuf; ifrp<(struct ifreq *)&((char *)ifrbuf)[ifc.ifc_len]; ifrp++){
    #ifdef __FreeBSD__
      adj = ifrp->ifr_addr.sa_len - sizeof (struct sockaddr);
      if(adj < 0){
        adj = 0;
      }
    #endif
    printf("%s:", ifrp->ifr_name);
    if(ioctl(sfd, SIOCGIFADDR, ifrp) < 0){
      putchar('\n');
    }else{
      printf(" %s\n", inet_ntoa(((struct sockaddr_in *)&ifrp->ifr_addr)->sin_addr));
    }
    ifrp = (struct ifreq *)&((char *)ifrp)[adj];
  }
  return 0;
}
