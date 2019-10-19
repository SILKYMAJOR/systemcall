#include <sys/utsname.h>
#include <stdio.h>

int main(){
  struct utsname buf;
  
  if(uname(&buf) < 0){
    perror("uname error");
    return 1;
  }
  
  printf("%s %s %s %s %s\n",
    buf.sysname,
    buf.nodename,
    buf.release,
    buf.version,
    buf.machine
  );
  return 0;  
}
