#include <unistd.h>
#include <pwd.h>
#include <stdio.h>

int main(){
  uid_t euid;
  struct passwd *pw;
  euid = geteuid();

  if((pw = getpwuid(euid)) == NULL){
    printf("%u\n", euid);
  }else{
    printf("%s\n", pw->pw_name);
  }
  return 0;
}
