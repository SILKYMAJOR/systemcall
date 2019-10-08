#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  off_t p, file_size;
  int pagesize;
  size_t len;
  char *mp;

  pagesize = getpagesize();

  if((file_size = lseek(0, 0, SEEK_END)) < 0){
    perror("lseek error");
    return 1;
  }
  
  len = pagesize;

  for(p=0; p<file_size; p+=len){
    if(file_size - p < pagesize){
      len = file_size - p;
    }
    if((mp = mmap(0, len, PROT_READ, MAP_PRIVATE, 0, p)) == MAP_FAILED){
      perror("mmap error");
      return 1;
    }

    write(1, mp, len);

    if(munmap(mp, len) < 0){
      perror("munmup error");
      return 1;
    }
  }
  return 0;
}
