#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 8

int main(){
  int fd, i;
  struct stat sb;
  char buf[BUF_SIZE];
  char *mm;

  memset(buf, 0, BUF_SIZE);

  if((fd = open("file.txt", O_CREAT|O_RDWR|O_TRUNC, 0644)) < 0){
    perror("open error");
    return 1;
  }

  write(fd, buf, BUF_SIZE);

  if(fstat(fd, &sb) == -1){
    perror("fstat error");
    return 1;
  }

  if((mm = mmap(NULL, sb.st_size, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED){
    perror("mmap error");
    return 1;
  }

  for(i=0; i<sb.st_size-2; i++)
    mm[i] = 'a' +i;
  
  mm[sb.st_size-2] = '\n';
  mm[sb.st_size-1] = '\0';

  msync(mm, sb.st_size, MS_SYNC);

  for(i=0; i<10; i++)
    printf("mm[%d] => %c\n", i, mm[i]);

  munmap(mm, sb.st_size);

  close(fd);

  return 0;
}
