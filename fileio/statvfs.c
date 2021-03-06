#include <sys/statvfs.h>
#include <stdio.h>
#include <stdint.h>

int main(){
  struct statvfs buf;
  if(statvfs(".", &buf) <0){
    perror("statvfs error");
    return 1;
  }
  printf("f_bsize = %lu, f_frsize = %lu\n", buf.f_bsize , buf.f_frsize);
  printf("f_blocks = %ju, f_bfree = %ju, f_bavail = %ju\n", (uintmax_t)buf.f_blocks, (uintmax_t)buf.f_bfree, (uintmax_t)buf.f_bavail);
  printf("f_files = %ju, f_ffree = %ju, f_favail = %ju\n", (uintmax_t)buf.f_files, (uintmax_t)buf.f_ffree, (uintmax_t)buf.f_favail);
  printf("f_fsid = %#lx, f_flag = %#lx, f_namemax = %lu\n", buf.f_fsid, buf.f_flag, buf.f_namemax);
  return 0;
}
