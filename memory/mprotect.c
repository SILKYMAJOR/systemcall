#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  int pagesize;
  size_t len;
  char* mp;

  pagesize = getpagesize();
  len = pagesize;

  mp = mmap(0, len, PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
  if(mp == MAP_FAILED){
    perror("mmap error");
    return 1;
  }
  if(mprotect(mp, len, PROT_READ) < 0){
    perror("mprotect error");
    return 1;
  }
  *mp = 1;
  return 0;

}
