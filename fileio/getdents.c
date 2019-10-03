#ifdef __linux__
# include <unistd.h>
# include <sys/syscall.h>
# define getdents(fd, dirp, count) syscall(SYS_getdents, fd, dirp, count)
struct linux_dirent{
  unsigned long d_ino;
  unsigned long d_off;
  unsigned short d_reclen;
  char d_name[];
};
# define dirent linux_dirent
#else
# include <dirent.h>
#endif

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  int i, d_size;
  int fd;
  struct dirent *dp;
  char buf[4096];

  if((fd = open("./", O_RDONLY)) < 0){
    perror("open error");
    return 1;  
  }

  while((d_size = getdents(fd, (void *)buf, sizeof buf)) > 0){
    for(i=0;i<d_size;i+=dp->d_reclen){
      dp = (struct dirent *)&buf[i];
      printf("%s\n", dp->d_name);
    
    }
  }
  if(d_size < 0){
    perror("getdents error");
    return 1;  
  }
  return 0;
}
